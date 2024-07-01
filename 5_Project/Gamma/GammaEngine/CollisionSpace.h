#pragma once
namespace GammaEngine {
	class Collider;
	class CollisionSpace
	{
		public:
			CollisionSpace();
			~CollisionSpace();

		public:
			void Frame();
			void Add(Collider*);
			void Remove(Collider*);
			bool RemoveEmptySpace();
			bool IsEmpty();
		public:
			static CollisionSpace* root;
			CollisionSpace* division[4];
			std::vector<Collider*>* colliderList;
			std::vector<Collider*>* removeBuffer;
			float areaSize;
			vector2 center;
			int depth;
			static int maxDepth;
			static float minAreaSize;
	};
};
