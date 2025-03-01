#include "Quat.h"

#include <cmath>

namespace Math
{
	Quat::Quat() :
		qx(0.0f),
		qy(0.0f),
		qz(0.0f),
		qw(1.0f)
	{
	}

	// Copy Constructor
	Quat::Quat(const Quat& qIn) : 
		qm(qIn.qm) 
	{
	}

	Quat::Quat(const Vector4& vect, const float real)
		: qm(_mm_set_ps(real, vect.Z(), vect.Y(), vect.X())) {
	}

	Quat::Quat(const float vx, const float vy, const float vz, const float real)
		: qm(_mm_set_ps(real, vz, vy, vx)) {
	}

	Quat::Quat(const Matrix4x4& mIn) {
		set(mIn);
	}

	// Constructor for identity rotation
	Quat::Quat(const MatrixSpecialType value) {
		if (value == IDENTITY)
			this->qm = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

		else
			this->qm = _mm_setzero_ps();
	}

	// Constructor for rotation by one angle
	Quat::Quat(RotType type, const float angle) {
		set(type, angle);
	}

	// Constructor for 3-axis rotation
	Quat::Quat(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2) {
		set(type, angle_0, angle_1, angle_2);
	}

	// Constructor for axis-angle rotation
	Quat::Quat(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians) {
		set(ROT_AXIS_ANGLE, vAxis, angle_radians);
	}

	// Constructor for orientation quaternion
	Quat::Quat(const RotOrientType, const Vector4& dof, const Vector4& up) {
		set(ROT_ORIENT, dof, up);
	}

	// Destructor
	Quat::~Quat() {}

	// Set quaternion from matrix
	void Quat::set(const Matrix4x4& m) {
		float trace = m.M0() + m.M5() + m.M10();

		if (trace > 0.0f) {
			float s = 0.5f / std::sqrtf(trace + 1.0f);
			this->qm = _mm_set_ps(0.25f / s, (m.M6() - m.M9()) * s, (m.M8() - m.M2()) * s, (m.M1() - m.M4()) * s);
		}
		else {
			if (m.M0() > m.M5() && m.M0() > m.M10()) {
				float s = 2.0f * sqrtf(1.0f + m.M0() - m.M5() - m.M10());
				this->qm = _mm_set_ps((m.M6() - m.M9()) / s, 0.25f * s, (m.M1() + m.M4()) / s, (m.M8() + m.M2()) / s);
			}
			else if (m.M5() > m.M10()) {
				float s = 2.0f * sqrtf(1.0f + m.M5() - m.M0() - m.M10());
				this->qm = _mm_set_ps((m.M8() - m.M2()) / s, (m.M1() + m.M4()) / s, 0.25f * s, (m.M6() + m.M9()) / s);
			}
			else {
				float s = 2.0f * sqrtf(1.0f + m.M10() - m.M0() - m.M5());
				this->qm = _mm_set_ps((m.M1() - m.M4()) / s, (m.M8() + m.M2()) / s, (m.M6() + m.M9()) / s, 0.25f * s);
			}
		}
	}

	// Set identity quaternion
	void Quat::set(MatrixSpecialType type) {
		if (type == IDENTITY)
			this->qm = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

		else
			this->qm = _mm_setzero_ps();
	}

	// Set quaternion by rotation type and angle
	void Quat::set(RotType type, const float angle) {
		float halfAngle = angle * 0.5f;
		float sinHalfAngle = sinf(halfAngle);
		float cosHalfAngle = cosf(halfAngle);

		switch (type) {
		case ROT_X:
			this->qm = _mm_set_ps(cosHalfAngle, sinHalfAngle, 0.0f, 0.0f);
			break;
		case ROT_Y:
			this->qm = _mm_set_ps(cosHalfAngle, 0.0f, sinHalfAngle, 0.0f);
			break;
		case ROT_Z:
			this->qm = _mm_set_ps(cosHalfAngle, 0.0f, 0.0f, sinHalfAngle);
			break;
		}
	}

	// Set quaternion for 3-axis rotation
	void Quat::set(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2) {
		if (type == ROT_XYZ) {
			setRotXYZ(angle_0, angle_1, angle_2);
		}
	}

	// Set quaternion for axis-angle rotation
	void Quat::set(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians) {
		setRotAxisAngle(vAxis, angle_radians);
	}

	void Quat::set(const RotOrientType, const Vector4& dof, const Vector4& up)
	{
		Matrix4x4 rotationMatrix(ROT_ORIENT, dof, up);
		set(rotationMatrix);
	}

	// Set quaternion components
	void Quat::set(const float vx, const float vy, const float vz, const float real) {
		this->qm = _mm_set_ps(real, vz, vy, vx);
	}

	// Get angle of rotation
	const float Quat::getAngle() const {
		return 2.0f * acosf(this->qw);
	}

	// Get vector component of quaternion
	void Quat::getVect(Vector4& vOut) const {
		vOut = Vector4(this->qx, this->qy, this->qz);
	}

	// Get axis of rotation
	void Quat::getAxis(Vector4& vOut) const {
		float sinHalfAngle = sqrtf(1.0f - this->qw * this->qw);
		if (sinHalfAngle < 0.001f) {
			vOut.set(1.0f, 0.0f, 0.0f);
		}
		else {
			vOut.set(this->qx / sinHalfAngle, this->qy / sinHalfAngle, this->qz / sinHalfAngle);
		}
	}

	// Dot product of two quaternions
	const float Quat::dot(const Quat& qin) const {
		return this->qx * qin.qx + this->qy * qin.qy + this->qz * qin.qz + this->qw * qin.qw;
	}

	// Magnitude of quaternion
	const float Quat::mag() const {
		return sqrtf(this->dot(*this));
	}

	// Magnitude squared of quaternion
	const float Quat::magSquared() const {
		return this->dot(*this);
	}

	// Inverse magnitude of quaternion
	const float Quat::invMag() const {
		return 1.0f / this->mag();
	}

	// Conjugate quaternion in place
	Quat& Quat::conj() {
		this->qx = -this->qx;
		this->qy = -this->qy;
		this->qz = -this->qz;
		return *this;
	}

	// Return conjugate quaternion
	Quat Quat::getConj() const {
		return Quat(-this->qx, -this->qy, -this->qz, this->qw);
	}

	// Inverse quaternion in place
	Quat& Quat::inv() {
		__m128 magSq = _mm_set1_ps(this->magSquared());
		if (magSq.m128_f32[0] > 0.0f) {
			this->qm = _mm_div_ps(this->getConj().qm, magSq);
		}
		return *this;
	}

	// Return inverse quaternion
	Quat Quat::getInv() const {
		Quat result = *this;
		return result.inv();
	}

	// Normalize quaternion in place
	Quat& Quat::norm() {
		float magnitude = this->mag();
		if (magnitude > 0.0f) {
			float invMag = 1.0f / magnitude;
			this->qx *= invMag;
			this->qy *= invMag;
			this->qz *= invMag;
			this->qw *= invMag;
		}
		return *this;
	}

	// Return normalized quaternion
	Quat Quat::getNorm() const {
		Quat temp = *this;
		return temp.norm();
	}

	// Quaternion multiplication
	Quat Quat::operator*(const Quat& q) const {
		return Quat(
			this->qw * this->qx + this->qx * this->qw + this->qy * this->qz - this->qz * this->qy,
			this->qw * this->qy - this->qx * this->qz + this->qy * this->qw + this->qz * this->qx,
			this->qw * this->qz + this->qx * this->qy - this->qy * this->qx + this->qz * this->qw,
			this->qw * this->qw - this->qx * this->qx - this->qy * this->qy - this->qz * this->qz
		);
	}

	// Quaternion multiplication assignment
	const Quat& Quat::operator*=(const Quat& q) {
		*this = *this * q;
		return *this;
	}

	// Quaternion scalar multiplication
	Quat Quat::operator*(const float a) const {
		return Quat(this->qx * a, this->qy * a, this->qz * a, this->qw * a);
	}

	// Quaternion scalar multiplication assignment
	const Quat& Quat::operator*=(const float a) {
		this->qx *= a;
		this->qy *= a;
		this->qz *= a;
		this->qw *= a;
		return *this;
	}

	// Quaternion division by quaternion
	Quat Quat::operator/(const Quat& q) const {
		return *this * q.getInv();
	}

	// Quaternion division assignment
	const Quat& Quat::operator/=(const Quat& q) {
		*this = *this / q;
		return *this;
	}

	// Quaternion division by scalar
	Quat Quat::operator/(const float a) const {
		return Quat(this->qx / a, this->qy / a, this->qz / a, this->qw / a);
	}

	// Quaternion division by scalar assignment
	const Quat& Quat::operator/=(const float a) {
		this->qx /= a;
		this->qy /= a;
		this->qz /= a;
		this->qw /= a;
		return *this;
	}

	// Quaternion conjugate-linear operation vOut = Quat * vIn * Quat.conj()
	void Quat::Lqvqc(const Vector4& vIn, Vector4& vOut) const {
		Quat vq(vIn, 0.0f);
		Quat result = (*this * vq) * this->getConj();
		result.getVect(vOut);
	}

	// Quaternion conjugate-linear operation vOut = Quat.conj() * vIn * Quat
	void Quat::Lqcvq(const Vector4& vIn, Vector4& vOut) const {
		Quat vq(vIn, 0.0f);
		Quat result = (this->getConj() * vq) * (*this);
		result.getVect(vOut);
	}

	// Helper function to set quaternion for 3-axis rotation
	void Quat::setRotXYZ(const float a, const float b, const float c) {
		Quat qX(ROT_X, a);
		Quat qY(ROT_Y, b);
		Quat qZ(ROT_Z, c);
		*this = qX * qY * qZ;
	}

	// Helper function to set quaternion for axis-angle rotation
	void Quat::setRotAxisAngle(const Vector4& axis, const float angle) {
		float halfAngle = angle * 0.5f;
		float sinHalfAngle = sinf(halfAngle);
		float cosHalfAngle = cosf(halfAngle);
		this->qm = _mm_set_ps(cosHalfAngle, axis.Z() * sinHalfAngle, axis.Y() * sinHalfAngle, axis.X() * sinHalfAngle);
	}

	// Test function: isNormalized
	const bool Quat::isNormalized(const float epsilon) const {
		return fabs(this->magSquared() - 1.0f) < epsilon;
	}

	const Quat& Quat::operator=(const Quat& q)
	{
		this->qm = q.qm;
		return *this;
	}
}
