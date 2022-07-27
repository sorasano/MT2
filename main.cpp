#include "Vector3.h"
#include "DxLib.h"

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	const int WindowWidth = 1024;
	const int WindowHeight = 576;
	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 64);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 0.0f, -100.0f),
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 1.0f, 0.0f)
	);
	Vector3 position(0, 0, 0);
	Vector3 velocity(0.0f, 0.0f, 0.5f);
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//çXêV
		position += velocity;

		//ï`âÊ
		ClearDrawScreen();
		DrawSphere3D(position,80.0f,32,GetColor(255,0,0),GetColor(255,255,255),TRUE);
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z};
	return DrawSphere3D(centerPos,r,DivNum,DifColor,SpcColor,FillFlag);
}
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };

	return DrawLine3D(p1,p2,Color);
}
