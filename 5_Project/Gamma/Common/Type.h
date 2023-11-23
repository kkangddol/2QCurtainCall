#pragma once
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "Matrix.h"

/// <summary>
/// Tween의 재생 정보를 표현하는 enum 타입 
/// </summary>

enum PLAYBACK
{
	ONCE_FORWARD,//1회 정방향
	ONCE_BACKWARD,//1회 역방향
	ONCE_PINGPONG,//1회 왔다갔다
	LOOP_FORWARD,//반복 정방향
	LOOP_BACKWARD,//반복 역방향
	LOOP_PINGPONG//반복 왔다갔다
};
