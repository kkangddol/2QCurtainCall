#pragma once
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "Matrix.h"

/// <summary>
/// Tween�� ��� ������ ǥ���ϴ� enum Ÿ�� 
/// </summary>

enum PLAYBACK
{
	ONCE_FORWARD,//1ȸ ������
	ONCE_BACKWARD,//1ȸ ������
	ONCE_PINGPONG,//1ȸ �Դٰ���
	LOOP_FORWARD,//�ݺ� ������
	LOOP_BACKWARD,//�ݺ� ������
	LOOP_PINGPONG//�ݺ� �Դٰ���
};
