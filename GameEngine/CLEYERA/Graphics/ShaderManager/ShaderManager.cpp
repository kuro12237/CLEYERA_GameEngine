#include "ShaderManager.h"
#include <iostream>
using namespace Microsoft::WRL;

void CLEYERA::Graphics::Shader::ShaderManager::Init() {

   HRESULT hr = {};

   hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&utils_));
   assert(SUCCEEDED(hr));

   hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler_));
   assert(SUCCEEDED(hr));
}

std::vector<char> CLEYERA::Graphics::Shader::ShaderManager::CompileShader(const std::filesystem::path &hlslFilename) {

   HRESULT hr;

   std::ifstream infile(hlslFilename, std::ifstream::binary);
   if (!infile) {
      assert(false && "Failed to open shader file.");
      return {};
   }

   std::wstring fileName = hlslFilename.filename().wstring();
   std::stringstream strstream;
   strstream << infile.rdbuf();
   std::string shaderCode = strstream.str();

   // DXC ライブラリの作成
   ComPtr<IDxcLibrary> lib;
   hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&lib));
   assert(SUCCEEDED(hr) && "Failed to create DXC Library");

   // DXC コンパイラの作成
   ComPtr<IDxcCompiler> compiler;
   hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
   assert(SUCCEEDED(hr) && "Failed to create DXC Compiler");

   // ソースコードのエンコーディング
   ComPtr<IDxcBlobEncoding> source;
   hr = lib->CreateBlobWithEncodingFromPinned(shaderCode.data(), static_cast<UINT32>(shaderCode.size()), CP_UTF8, &source);
   assert(SUCCEEDED(hr) && "Failed to create DXC BlobEncoding");

   // インクルードハンドラ作成
   ComPtr<IDxcIncludeHandler> includeHandler;
   lib->CreateIncludeHandler(&includeHandler);

   // コンパイルオプション
   std::vector<LPCWSTR> arguments = {
       L"-E",           L"main",    // エントリーポイント
       L"-T",           L"lib_6_6", // ターゲットプロファイル
       L"-O3",                      // 最適化レベル
       L"-Zi",
       L"-Qembed_debug" // デバッグ情報
   };

   // シェーダのコンパイル
   ComPtr<IDxcOperationResult> dxcResult;
   hr = compiler->Compile(source.Get(), fileName.c_str(), L"main", L"lib_6_6", arguments.data(), static_cast<UINT32>(arguments.size()), nullptr, 0, includeHandler.Get(), &dxcResult);
   assert(SUCCEEDED(hr) && "Failed to start DXC compilation");

   // コンパイル結果の確認
   dxcResult->GetStatus(&hr);
   if (FAILED(hr)) {
      ComPtr<IDxcBlobEncoding> errorBuffer;
      dxcResult->GetErrorBuffer(&errorBuffer);
      if (errorBuffer) {
         std::cerr << "Shader compilation error: " << (const char *)errorBuffer->GetBufferPointer() << std::endl;
      }
      assert(false && "Shader compilation failed");
      return {};
   }

   // バイナリ取得
   ComPtr<IDxcBlob> blob;
   dxcResult->GetResult(&blob);
   std::vector<char> result(blob->GetBufferSize());
   memcpy(result.data(), blob->GetBufferPointer(), blob->GetBufferSize());

   return result;
}

IDxcBlob *CLEYERA::Graphics::Shader::ShaderManager::CompilerShaderFanc(const std::wstring &filePath, const wchar_t *profile) {


   // LogManager::Log(LogManager::ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));

   IDxcBlobEncoding *shaderSource = nullptr;
   HRESULT hr = utils_->LoadFile(filePath.c_str(), nullptr, &shaderSource);

   assert(SUCCEEDED(hr));
   DxcBuffer shaderSourceBuffer;
   shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
   shaderSourceBuffer.Size = shaderSource->GetBufferSize();
   shaderSourceBuffer.Encoding = DXC_CP_UTF8;

   LPCWSTR arguments[] = {
       filePath.c_str(), L"-E", L"main", L"-T", profile, L"-Zi", L"-Qembed_debug", L"-Od", L"-Zpr",
   };

   IDxcResult *shaderResult = nullptr;
   hr = compiler_->Compile(&shaderSourceBuffer, arguments, _countof(arguments), includeHandler.Get(), IID_PPV_ARGS(&shaderResult));

   assert(SUCCEEDED(hr));

   IDxcBlobUtf8 *shaderError = nullptr;
   shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
   if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
      LogManager::Log(shaderError->GetStringPointer());
		
      assert(false);
   }

   IDxcBlob *shaderBlob = nullptr;
   hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
   assert(SUCCEEDED(hr));

   // LogManager::Log(LogManager::ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));

   shaderSource->Release();
   shaderResult->Release();
   return shaderBlob;
}
