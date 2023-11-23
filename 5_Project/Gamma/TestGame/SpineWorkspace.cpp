#include "SpineWorkspace.h"
#include "GammaEngine.h"
#include "SandBox.h"

using namespace GammaEngine;

SpineWorkSpace::SpineWorkSpace()
{
	//Create Scene
	Scene* spineScene = SceneManager::CreateScene("spineScene");
	spineScene->SetInitializer(SpineSceneInit);
	SceneManager::LoadScene("spineScene");
}
