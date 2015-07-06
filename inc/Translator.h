/**
 * @file   Translator.h
 * @brief  JSON-MessagePack変換
 * @author kyo
 * @date   2015/07/06
 */
#ifndef CNVMSG_TRANSLATOR_H_
#define CNVMSG_TRANSLATOR_H_

#include "Common.h"
#include "CommandLine.h"
#include <memory>
#include <vector>
#include <string>

/** Convert MessagePack */
namespace cnvmsg
{
/**
 * JSON-MessagePack変換
 */
class Translator
{
private:
  //! コピー防止
  DISALLOW_COPY_AND_ASSIGN(Translator);

public:
  /** コンストラクタ */
  Translator();

  /** 仮想デストラクタ */
  virtual ~Translator();

  /**
   * 変換
   * @param[in] commandline コマンドライン引数の情報
   */
  void Translate(const CommandLine& command);
};
}
#endif // CNVMSG_TRANSLATOR_H_
