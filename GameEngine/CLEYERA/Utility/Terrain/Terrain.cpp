#include "Terrain.h"

void CLEYERA::Manager::Terrain::Init() {
   modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
   renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();
   colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();
   objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();

   modelHandle_ = modelManager_->LoadModel(dfFilePath_, objName_);

   gameObj_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();

   gameObj_->Create(modelHandle_);
   gameObj_->SetScale(scaleTerrain_);
   gameObj_->SetRotate(rotateTerrain_);
   gameObj_->SetTranslate(translateTerrain_);
   gameObj_->SetName(objName_);
   this->gameObj_->Update();

   renderManager_->PushObj(gameObj_);
   objectManager_->AddObject(gameObj_);

   CLEYERA::Model3d::MeshData *meshData = gameObj_->GetModel().lock()->GetMeshData();
   CLEYERA::Model3d::system::VertexData data = meshData->GetData();
   size_t triangleCount = data.indecs.size() / 3;

   triCollider_.resize(triangleCount);

   for (size_t i = 0; i < triangleCount; i++) {
      for (size_t vert = 0; vert < 3; vert++) {
         size_t vertexIndex = data.indecs[i * 3 + vert];
         triCollider_[i].vertex[vert].x = data.vertices[vertexIndex].pos.x;
         triCollider_[i].vertex[vert].y = data.vertices[vertexIndex].pos.y;
         triCollider_[i].vertex[vert].z = data.vertices[vertexIndex].pos.z;
      }
   }

   line_ = std::make_shared<Model3d::Line3d>();
   line_->Init(triangleCount * 3);

   colors_.resize(triangleCount * 3 * 2);
   positions_.resize(triangleCount * 3 * 2);

   line_->SetLinePos(positions_);
   line_->SetLineColor(colors_);
   line_->SetRotate(rotateTerrain_);
   line_->SetTranslate(translateTerrain_);
   line_->SetScale(scaleTerrain_);
   line_->SetMat4x4(mat_);

   mat_.Identity();

   renderManager_->PushLine3d(line_);

   size_t index = 0;

   for (size_t i = 0; i < triangleCount; i++) {
      const auto &tri = triCollider_[i];
      using Vec3 = Math::Vector::Vec3;

      const Vec3 &v0 = tri.vertex[0];
      const Vec3 &v1 = tri.vertex[1];
      const Vec3 &v2 = tri.vertex[2];

      // v0 → v1
      positions_[index++] = v0;
      positions_[index++] = v1;

      // v1 → v2
      positions_[index++] = v1;
      positions_[index++] = v2;

      // v2 → v0
      positions_[index++] = v2;
      positions_[index++] = v0;
   }
   for (size_t i = 0; i < colors_.size(); i++) {
      colors_[i] = {0.0f, 0.0f, 0.0f, 1.0f};
   }
   line_->Update();
}

void CLEYERA::Manager::Terrain::Update() {

   for (size_t i = 0; i < triCollider_.size(); i++) {

      triCollider_[i].edgeVec[0] = triCollider_[i].vertex[1] - triCollider_[i].vertex[0];
      triCollider_[i].edgeVec[1] = triCollider_[i].vertex[2] - triCollider_[i].vertex[1];
      triCollider_[i].edgeVec[2] = triCollider_[i].vertex[0] - triCollider_[i].vertex[2];
      triCollider_[i].normal = Math::Vector::Func::Cross(triCollider_[i].edgeVec[0], triCollider_[i].edgeVec[1]);
      triCollider_[i].dot = Math::Vector::Func::Dot(triCollider_[i].normal * -1, triCollider_[i].vertex[0]);
   }
}

void CLEYERA::Manager::Terrain::Finalize() {
   gameObj_.reset();
   line_.reset();
}

void CLEYERA::Manager::Terrain::CheckObjct(Math::Vector::Vec3 &pos, const float &size) {

   using Vec3 = Math::Vector::Vec3;

   for (size_t i = 0; i < triCollider_.size(); i++) {

      if (triCollider_[i].contains(pos)) {

         pos.y = triCollider_[i].getY(pos) + size;
      }
   }
}
