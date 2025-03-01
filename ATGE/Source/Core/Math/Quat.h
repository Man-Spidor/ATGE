#pragma once

#include "Matrix.h"
#include "EnumDefine.h"

/*************************************************************************
*
* This class contains functions and data structure for a 4-dimensional
* Quaternions.  The quaternions are internally stored interms of the
* imaginary components (x,y,z) and the real components (real).
*
* In the Math library, quaternions can be thought of as "rotational"
* matrices, everything that you can represent with rotational matrices
* you can use with quaternions.  Such as quaternion concatenation,
* inverses, transpose, normalize, multiplying with matrices, and with
* vectors.
*
*
**************************************************************************/

namespace Math
{

	class Quat final : public Align16
	{
	public:
		explicit Quat();
		Quat(const Quat& qIn);
		Quat(const Vector4& vect, const float real);
		Quat(const float vx, const float vy, const float vz, const float real);
		explicit Quat(const Matrix4x4& mIn);
		explicit Quat(const MatrixSpecialType  value);
		// Rotations by 1 angle:
		Quat(RotType type, const float angle);
		// Rotations by 3 angle:
		Quat(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
		// Axis and Angle:
		Quat(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians);
		// Orientation:
		Quat(const RotOrientType, const Vector4& dof, const Vector4& up);
		// default Destructor 
		~Quat(void);


		void set(MatrixSpecialType type);
		void set(RotType type, const float angle);
		void set(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
		void set(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians);
		void set(const RotOrientType, const Vector4& dof, const Vector4& up);
		void set(const float vx, const float vy, const float vz, const float real);

		inline float& operator[](const x_enum value) { return this->qx; };
		inline float& operator[](const y_enum value) { return this->qy; };
		inline float& operator[](const z_enum value) { return this->qz; };
		inline float& operator[](const w_enum value) { return this->qw; };

		inline const float operator[](const x_enum value) const { return this->qx; };
		inline const float operator[](const y_enum value) const { return this->qy; };
		inline const float operator[](const z_enum value) const { return this->qz; };
		inline const float operator[](const w_enum value) const { return this->qw; };

		// set by Vector component, does not set the real component
		void setVect(const Vector4& vect);

		// set real, vector	
		void set(const Vector4& vect, const float real);

		// set by matrix ( essentially Quat to Matrix conversion )
		void set(const Matrix4x4& m);

		// Get Angle of rotation about the axis of rotation
		const float getAngle(void) const;

		// Get Vector component
		void getVect(Vector4& vOut) const;


		// Get Axis of rotation
		void getAxis(Vector4& vOut) const;

		// General member functions

			// dot product of two quaternions (4D)
		const float dot(const Quat& qin) const;

		// Magnitude

			// magnitude 
		const float mag(void) const;

		// magnitude Squared (Remember for Unit Quats, magSquared == 1.0f );
		const float magSquared(void) const;

		// inverse magnitude
		const float invMag(void) const;

		// Conjugate

			// Conjugate Quat in place
		Quat& conj(void);

		// Return conjuate Quat
		Quat getConj(void) const;

		// Transpose

			// Inverse Quat in place
		Quat& T(void);

		// Return inverse Quat	
		Quat getT(void) const;

		// Inverse

			// Inverse Quat in place
		Quat& inv(void);

		// Return inverse Quat
		Quat getInv(void) const;

		// Normalize

			// Normalize Quat in place
		Quat& norm(void);

		// Return Normalize Quat
		Quat getNorm(void) const;

		// Linear Operator

		// Linear Operator vout = Quat * Vector * Quat(conjugate)
		// vOut = Quat * vIn * Quat.conj()
		void Lqvqc(const Vector4& vIn, Vector4& vOut) const;

		// Linear Operator  vOut = Quat(conjugate) * Vector4or * Quat
		// vOut = Quat.conj() * vIn * Quat		
		void Lqcvq(const Vector4& vIn, Vector4& vOut) const;


		// Test functions

		// Return true if the two Quats are equal within epsilon of each other
		const bool isEqual(const Quat& qin, const float epsilon = 0.0f) const;

		// Return true if the two Quats are equivalent within epsilon of each other
		const bool isEquivalent(const Quat& qin, const float epsilon = 0.0f) const;

		// Return true if the two Quats are equal but negative in direction within epsilon of each other
		const bool isNegEqual(const Quat& qin, const float epsilon = 0.0f) const;

		// Return true if the two Quats are equal but conjugate within epsilon of each other
		const bool isConjugateEqual(const Quat& qin, const float epsilon = 0.0f) const;

		// Return true if the Quat represents Identity Rotation
		const bool isIdentity(const float epsilon = 0.0f) const;

		// Return true if the Quat is normalized
		const bool isNormalized(const float epsilon = 0.0f) const;

		// Return true if the Quat is a ZERO quat
		const bool isZero(const float epsilon = 0.0f) const;

		const Quat& operator=(const Quat& q);

		const Quat& operator=(const Matrix4x4& m);

		const Quat operator+(void) const;

		const Quat operator+(const Quat& q) const;

		const Quat& operator+=(const Quat& q);

		Quat operator+(const float a) const;

		const Quat& operator+=(const float a);

		friend Quat operator+(const float a, const Quat& q);

		const Quat operator-(void) const;

		Quat operator-(const Quat& q) const;

		const Quat& operator-=(const Quat& q);

		Quat operator-(const float a) const;

		const Quat& operator-=(const float a);

		friend Quat operator-(const float a, const Quat& q);

		Quat operator*(const Quat& q) const;

		const Quat& operator*=(const Quat& q);

		Quat operator*(const float a) const;

		const Quat& operator*=(const float a);

		friend Quat operator*(const float a, const Quat& q);

		const Quat& operator*=(const Matrix4x4& m);

		Matrix4x4 operator*(const Matrix4x4& m) const;

		Quat operator/(const Quat& q) const;

		const Quat& operator/=(const Quat& q);

		Quat operator/(const float a) const;

		const Quat& operator/=(const float a);

		friend Quat operator/(const float a, const Quat& q);

		const Quat multByElement(const Quat& q) const;


	private:
		void setRotX(const float a);
		void setRotXYZ(const float a, const float b, const float c);
		void setRotY(const float a);
		void setRotZ(const float a);
		void setRotAxisAngle(const Vector4& axis, const float angle);

	private:

		// anonymous union
		union
		{
			__m128	qm;

			// anonymous struct
			struct
			{
				float qx;
				float qy;
				float qz;
				float qw;
			};
		};
	};
}
