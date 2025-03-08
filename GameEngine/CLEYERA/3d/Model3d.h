#pragma once
#include"Vertex/Vertex.h"
#include <memory>

namespace CLEYERA {
namespace Model3d {

class Model {
 public:
   Model() {};
   ~Model() {};

   void Init();

   void Update();


 private:

	 std::unique_ptr<system::Vertex> vertex_ = nullptr;

};

}
} // namespace CLEYERA