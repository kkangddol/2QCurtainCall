// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#include "targetver.h"

#include "spine/spine.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
/*#define _HAS_STD_BYTE 0*/
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <set>
#include <string>



#include "Type.h"
#include "Util.h"
#include "GammaMath.h"
#include "GRX.h"

//base
#include "Singleton.h"
#include "resource.h"
#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "SoundSystem.h"
#include "Screen.h"
#include "Input.h"
#include "ParticleManager.h"
#include "EngineTime.h"
#include "TimerHandler.h"
#include "Timer.h"
#include "Tween.h"

//component
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

//render
#include "Letter.h"
#include "Render.h"
#include "Renderer.h"
#include "EllipseRenderer.h"
#include "RectangleRenderer.h"
#include "PolygonRenderer.h"
#include "BitmapRenderer.h"
#include "LineRenderer.h"
#include "TextRenderer.h"
#include "TextAnimationRenderer.h"
#include "Animation.h"
#include "Animator.h"

//collision
#include "Collider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "CollisionSystem.h"
#include "CollisionSpace.h"
#include "Rigidbody.h"
#include "Physics.h"
#include "ParticleSystem.h"

//sound
#include "AudioSource.h"



#include "Particle.h"
#include "ParticleEmitter.h"

//objectPool
#include "ObjectPool.h"

//UI
#include "UIElement.h"
#include "BoxUIElement.h"
#include "UITextSegment.h"
#include "UIPanel.h"

#include "TextAnimator.h"

//spine
#include "SpineModel.h"
#include "SpineRenderer.h"
#include "GammaTextureLoader.h"

#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DistantLight.h"
#include "LightAdapter.h"
#include "LightSystem.h"

//Entity
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"

//gamepad
#include "Gamepad.h"
#include "GamepadManager.h"


//effect
#include <GammaEffect.h>
#include <GammaPhysics.h>
#include "Debug.h"


#include "Engine.h"