#include "Vector3.h"
#include "DxLib.h"

//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,
	const Vector3& cameraTarget,
	const Vector3& cameraUp
);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	const int WindowWidth = 1024;
	const int WindowHeight = 576;
	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 64);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);


	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	//SetCameraPositionAndTargetAndUpVec(
	//	VGet(0.0f, 0.0f, -100.0f),
	//	VGet(0.0f, 0.0f, 0.0f),
	//	VGet(0.0f, 1.0f, 0.0f)
	//);

	//球
	Vector3 position(0, 0, 0);
	Vector3 velocity(0.0f, 0.0f, 0.5f);

	//カメラ
	Vector3 cameraPosition(0.0f, 0.0f, 50.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);

	SetCameraPositionAndTargetAndUpVec(cameraPosition, cameraTarget, cameraUp);

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = A.operator+=(B);
	Vector3 BC = B.operator+=(C);

	Vector3 n = AB.cross(BC);
	n.normalize();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//更新

		Vector3 v = ((A + B + C) / 3) + cameraPosition;
		v.normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.dot(n) < 0) {
			color = GetColor(255, 0, 0);
		}

		//描画
		ClearDrawScreen();

		//DrawSphere3D(position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);

		//法線の視覚化
		color = (100, 100, 255);
		DrawLine3D(A, A+n, color);
		DrawLine3D(B, B+n, color);
		DrawLine3D(C, C+n, color);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z };
	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };

	return DrawLine3D(p1, p2, Color);
}

int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,
	const Vector3& cameraTarget,
	const Vector3& cameraUp
) {
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = {cameraTarget.x,cameraTarget.y,cameraTarget.z};
	VECTOR up = {cameraUp.x,cameraUp.y,cameraUp.z};

	return SetCameraPositionAndTargetAndUpVec(position,target,up);
}
