// Copyright 2019 CryptoGarage
/**
 * @file cfdjs_node_addon.cpp
 *
 * @brief cfdのnode.js向けAPI実装ファイル
 */
#include <napi.h>  // NOLINT

#include <string>

#include "cfd/cfd_common.h"
#include "cfddlcjs/cfddlcjs_api_json.h"
#include "cfddlcjs/cfddlcjs_common.h"

using cfd::dlc::js::api::json::JsonMappingApi;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Function;
using Napi::Number;
using Napi::Object;
using Napi::String;
using Napi::TypeError;
using Napi::Value;

// -----------------------------------------------------------------------------
// API wrapper for node addon
// -----------------------------------------------------------------------------

namespace cfd {
namespace dlc {
namespace js {
namespace api {
namespace json {

/**
 * @brief NodeAddonのJSON APIテンプレート関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @param[in] call_function   cfdの呼び出し関数
 * @return 戻り値(JSON文字列)
 */
Value NodeAddonJsonApi(
    const CallbackInfo &information,
    std::function<std::string(const std::string &)> call_function) {
  Env env = information.Env();
  if (information.Length() < 1) {
    TypeError::New(env, "Invalid arguments.").ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!information[0].IsString()) {
    TypeError::New(env, "Wrong arguments.").ThrowAsJavaScriptException();
    return env.Null();
  }

  try {
    std::string json_message =
        call_function(information[0].As<String>().Utf8Value());
    return String::New(env, json_message.c_str());
  } catch (const std::exception &except) {
    // illegal route
    std::string errmsg = "exception=" + std::string(except.what());
    TypeError::New(env, errmsg).ThrowAsJavaScriptException();
    return env.Null();
  } catch (...) {
    // illegal route
    TypeError::New(env, "Illegal exception.").ThrowAsJavaScriptException();
    return env.Null();
  }
}

/**
 * @brief NodeAddonのJSON APIテンプレート関数(response only).
 * @param[in] information     node addon apiのコールバック情報
 * @param[in] call_function   cfdの呼び出し関数
 * @return 戻り値(JSON文字列)
 */
Value NodeAddonJsonResponseApi(const CallbackInfo &information,
                               std::function<std::string()> call_function) {
  Env env = information.Env();
  try {
    std::string json_message = call_function();
    return String::New(env, json_message.c_str());
  } catch (const std::exception &except) {
    // illegal route
    std::string errmsg = "exception=" + std::string(except.what());
    TypeError::New(env, errmsg).ThrowAsJavaScriptException();
    return env.Null();
  } catch (...) {
    // illegal route
    TypeError::New(env, "Illegal exception.").ThrowAsJavaScriptException();
    return env.Null();
  }
}

Value CreateFundTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateFundTransaction);
}

Value SignFundTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SignFundTransaction);
}

Value GetRawFundTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetRawFundTxSignature);
}

Value AddSignatureToFundTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::AddSignatureToFundTransaction);
}

Value CreateCet(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateCet);
}

Value CreateClosingTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::CreateClosingTransaction);
}

Value CreatePenaltyTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::CreatePenaltyTransaction);
}

Value SignClosingTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SignClosingTransaction);
}

Value VerifyFundTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyFundTxSignature);
}

Value CreateRefundTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateRefundTransaction);
}

Value CreateDlcTransactions(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateDlcTransactions);
}

Value GetRawCetSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetRawCetSignature);
}

Value GetRawCetSignatures(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetRawCetSignatures);
}

Value AddSignaturesToCet(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddSignaturesToCet);
}

Value VerifyCetSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyCetSignature);
}

Value VerifyCetSignatures(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyCetSignatures);
}

Value CreateMutualClosingTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::CreateMutualClosingTransaction);
}

Value GetRawMutualClosingTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::GetRawMutualClosingTxSignature);
}

Value AddSignaturesToMutualClosingTx(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::AddSignaturesToMutualClosingTx);
}

Value VerifyMutualClosingTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information,
                          JsonMappingApi::VerifyMutualClosingTxSignature);
}

Value GetRawRefundTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetRawRefundTxSignature);
}

Value AddSignaturesToRefundTx(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddSignaturesToRefundTx);
}

Value VerifyRefundTxSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyRefundTxSignature);
}

Value SchnorrSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SchnorrSign);
}

Value GetSchnorrPublicNonce(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetSchnorrPublicNonce);
}

/**
 * @brief JSON APIの生成初期化関数.
 * @param[in] env         環境情報
 * @param[out] exports    関数格納ポインタ
 */
void InitializeJsonApi(Env env, Object *exports) {
  cfd::Initialize();
  exports->Set(String::New(env, "CreateFundTransaction"),
               Function::New(env, CreateFundTransaction));
  exports->Set(String::New(env, "SignFundTransaction"),
               Function::New(env, SignFundTransaction));
  exports->Set(String::New(env, "GetRawFundTxSignature"),
               Function::New(env, GetRawFundTxSignature));
  exports->Set(String::New(env, "AddSignatureToFundTransaction"),
               Function::New(env, AddSignatureToFundTransaction));
  exports->Set(String::New(env, "VerifyFundTxSignature"),
               Function::New(env, VerifyFundTxSignature));
  exports->Set(String::New(env, "CreateCet"), Function::New(env, CreateCet));
  exports->Set(String::New(env, "CreateClosingTransaction"),
               Function::New(env, CreateClosingTransaction));
  exports->Set(String::New(env, "CreatePenaltyTransaction"),
               Function::New(env, CreatePenaltyTransaction));
  exports->Set(String::New(env, "SignClosingTransaction"),
               Function::New(env, SignClosingTransaction));
  exports->Set(String::New(env, "CreateRefundTransaction"),
               Function::New(env, CreateRefundTransaction));
  exports->Set(String::New(env, "CreateDlcTransactions"),
               Function::New(env, CreateDlcTransactions));
  exports->Set(String::New(env, "GetRawCetSignature"),
               Function::New(env, GetRawCetSignature));
  exports->Set(String::New(env, "GetRawCetSignatures"),
               Function::New(env, GetRawCetSignatures));
  exports->Set(String::New(env, "AddSignaturesToCet"),
               Function::New(env, AddSignaturesToCet));
  exports->Set(String::New(env, "VerifyCetSignature"),
               Function::New(env, VerifyCetSignature));
  exports->Set(String::New(env, "VerifyCetSignatures"),
               Function::New(env, VerifyCetSignatures));
  exports->Set(String::New(env, "CreateMutualClosingTransaction"),
               Function::New(env, CreateMutualClosingTransaction));
  exports->Set(String::New(env, "GetRawMutualClosingTxSignature"),
               Function::New(env, GetRawMutualClosingTxSignature));
  exports->Set(String::New(env, "AddSignaturesToMutualClosingTx"),
               Function::New(env, AddSignaturesToMutualClosingTx));
  exports->Set(String::New(env, "VerifyMutualClosingTxSignature"),
               Function::New(env, VerifyMutualClosingTxSignature));
  exports->Set(String::New(env, "GetRawRefundTxSignature"),
               Function::New(env, GetRawRefundTxSignature));
  exports->Set(String::New(env, "AddSignaturesToRefundTx"),
               Function::New(env, AddSignaturesToRefundTx));
  exports->Set(String::New(env, "VerifyRefundTxSignature"),
               Function::New(env, VerifyRefundTxSignature));
  exports->Set(String::New(env, "SchnorrSign"),
               Function::New(env, SchnorrSign));
  exports->Set(String::New(env, "GetSchnorrPublicNonce"),
               Function::New(env, GetSchnorrPublicNonce));
}

}  // namespace json
}  // namespace api
}  // namespace js
}  // namespace dlc
}  // namespace cfd
