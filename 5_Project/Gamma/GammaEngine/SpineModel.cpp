#include "stdafx.h"

using namespace GammaEngine;
std::unordered_map<std::string, SpineModel*>* SpineModel::spineModelMap;

GammaEngine::SpineModel::SpineModel(spine::Skeleton* skeleton, spine::AnimationStateData* animationStateData, spine::AnimationState* animationState):
	skeleton(skeleton),
	animationStateData(animationStateData),
	animationState(animationState)
{
	
}

void GammaEngine::SpineModel::Initialize()
{
	spineModelMap = new std::unordered_map<std::string, SpineModel*>();
}

SpineModel* GammaEngine::SpineModel::Create(std::string name, std::string atlasName, std::string jsonName)
{
	
	spine::Atlas* atlas;
	spine::SkeletonData* skeletonData;
	spine::AnimationStateData* animationStateData;
	
	atlas = new spine::Atlas(atlasName.c_str(), new TextureLoader());
	if (atlas->getPages().size() == 0) {
		//printf("Failed to load atlas");
		delete atlas;
		exit(0);
	}

	spine::SkeletonJson json(atlas);
	skeletonData = json.readSkeletonDataFile(jsonName.c_str());
	if (!skeletonData) {
		//printf("Failed to load skeleton data");
		delete atlas;
		exit(0);
	}
	animationStateData = new spine::AnimationStateData(skeletonData);
	auto animationState = new spine::AnimationState(animationStateData);

	auto spineModel = new SpineModel(new spine::Skeleton(skeletonData), animationStateData, animationState);
	spineModelMap->insert(std::make_pair(name, spineModel));
	
	return spineModel;
}

void GammaEngine::SpineModel::Update()
{
	animationState->update((float)Time::deltaTime);
	animationState->apply(*skeleton);
	skeleton->updateWorldTransform();
}

void GammaEngine::SpineModel::Render(Matrix3x3 worldMatrix, Material* material, std::vector<IEffect*>* appliedEffect)
{
 	for (size_t i = 0, n = skeleton->getSlots().size(); i < n; ++i) {
		spine::Slot* slot = skeleton->getDrawOrder()[i];

		spine::Attachment* attachment = slot->getAttachment();
		if (!attachment) continue;
		spine::BlendMode engineBlendMode;
		switch (slot->getData().getBlendMode()) {
		case spine::BlendMode::BlendMode_Normal:
			engineBlendMode = spine::BlendMode::BlendMode_Normal;
			break;
		case spine::BlendMode::BlendMode_Additive:
			engineBlendMode = spine::BlendMode::BlendMode_Additive;
			break;
		case spine::BlendMode::BlendMode_Multiply:
			engineBlendMode = spine::BlendMode::BlendMode_Multiply;
			break;
		case spine::BlendMode::BlendMode_Screen:
			engineBlendMode = spine::BlendMode::BlendMode_Screen;
			break;
		default:
			// unknown Spine blend mode, fall back to
			// normal blend mode 
			engineBlendMode = spine::BlendMode::BlendMode_Normal;
		}

    
        if (attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
            // Cast to an spRegionAttachment so we can get the rendererObject
            // and compute the world vertices
			spine::RegionAttachment* regionAttachment = (spine::RegionAttachment*)attachment;
			auto region = static_cast<spine::AtlasRegion*>(regionAttachment->getRegion());
			auto bone = slot->getBone();
			if (region)
			{
				std::wstring* bitmap = (std::wstring*)((spine::AtlasRegion*)regionAttachment->getRendererObject())->page->getRendererObject();

				vector2 regionSize;
				vector2 regionPos = vector2((float)region->x, (float)region->y);
				float regionRot = (float)region->degrees;
				if (regionRot == 90.0f)
				{
					regionSize=vector2((float)region->height, (float)region->width);
				}
				else
				{
					regionSize = vector2((float)region->width, (float)region->height);
				}

				vector2 attachmentSize = vector2(regionAttachment->getWidth(), regionAttachment->getHeight());
				vector2 attachmentPos = vector2(regionAttachment->getX(), -regionAttachment->getY());
				vector2 attachmentScale = vector2(regionAttachment->getScaleX(), regionAttachment->getScaleY());
				float attachmentRotation = regionAttachment->getRotation();
				Matrix3x3 attachmentMatrix = Matrix3x3::Rotate(-regionRot) *Matrix3x3::Scale(attachmentScale.x, attachmentScale.y)* Matrix3x3::Rotate(attachmentRotation) * Matrix3x3::Translation(attachmentPos.x, attachmentPos.y) ;
			
				vector2 boneScale = vector2(bone.getWorldScaleX(), bone.getWorldScaleY());
				vector2 bonePos = vector2(bone.getWorldX(), -bone.getWorldY());
				float boneRotx= bone.getWorldRotationX();
				float boneRoty= bone.getWorldRotationY();
			
				Matrix3x3 boneMatrix = Matrix3x3::Scale(boneScale.x, boneScale.y) * Matrix3x3::Rotate(boneRotx) * Matrix3x3::Translation(bonePos.x, bonePos.y);


				Matrix3x3 matrix = attachmentMatrix * boneMatrix * worldMatrix;
				GraphicSystem::DrawBitmap(*bitmap, regionSize, regionSize, regionPos, matrix, material, appliedEffect);
			}
        }
        else if (attachment->getRTTI().isExactly(spine::MeshAttachment::rtti)) {
			return;
        }

  
       
}
}
