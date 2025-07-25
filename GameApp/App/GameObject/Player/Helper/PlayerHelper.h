#pragma once

#include "CLEYERA.h"

class PlayerHelper {

public:

	/// <summary>
	/// 方向ベクトルを求める
	/// </summary>
	static Math::Vector::Vec3 CalcDirectVec(const Math::Vector::Vec3 & defV, float rotateY)
	{
		Math::Matrix::Mat4x4 rotateYMat = Math::Matrix::Func::RotateYMatrix(rotateY);
		return TransformWithPerspective(defV, rotateYMat);
	}

	/// <summary>
	/// Vector3にアフィン変換と透視補正を適用する
	/// </summary>
	static Math::Vector::Vec3 TransformWithPerspective(const Math::Vector::Vec3 & v,
												const Math::Matrix::Mat4x4 & m)
	{
		Math::Vector::Vec3 result = {
		(v.x * m.m[ 0 ][ 0 ]) + (v.y * m.m[ 1 ][ 0 ]) + (v.z * m.m[ 2 ][ 0 ]) + (1.0f * m.m[ 3 ][ 0 ]),
		(v.x * m.m[ 0 ][ 1 ]) + (v.y * m.m[ 1 ][ 1 ]) + (v.z * m.m[ 2 ][ 1 ]) + (1.0f * m.m[ 3 ][ 1 ]),
		(v.x * m.m[ 0 ][ 2 ]) + (v.y * m.m[ 1 ][ 2 ]) + (v.z * m.m[ 2 ][ 2 ]) + (1.0f * m.m[ 3 ][ 2 ]) };
		float w = (v.x * m.m[ 0 ][ 3 ]) + (v.y * m.m[ 1 ][ 3 ]) + (v.z * m.m[ 2 ][ 3 ]) + (1.0f * m.m[ 3 ][ 3 ]);

		// 0除算を避ける
		if ( w != 0.0f ) {
			result.x /= w;
			result.y /= w;
			result.z /= w;
		}

		return result;
	}


private:

	// インスタンス化禁止
	PlayerHelper() = delete;

};