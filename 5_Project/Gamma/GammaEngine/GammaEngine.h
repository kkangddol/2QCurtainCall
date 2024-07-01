#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
#include "spine/spine.h"
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <map>
#include "Type.h"
#include "Util.h"
#include "Render.h"
#include "GRX.h"
//base
#include "Singleton.h"
#include "resource.h"
#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "Screen.h"
#include "Input.h"
#include "EngineTime.h"
#include "TimerHandler.h"
#include "Timer.h"
#include "Tween.h"
#include "SoundSystem.h"


//component
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

//render
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

//sound
#include "AudioSource.h"
#include "SoundSystem.h"

// objectPool
#include "ObjectPool.h"

//Entity
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Engine.h"

#include "UIElement.h"

#include "TextAnimator.h"

//spine
#include "SpineModel.h"
#include "SpineRenderer.h"
#include "GammaTextureLoader.h"

//light
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DistantLight.h"
#include "LightAdapter.h"
#include "LightSystem.h"

//gamepad
#include "Gamepad.h"
#include "GamepadManager.h"
#include "../GammaEffect/GammaEffect.h"


#include "Debug.h"
