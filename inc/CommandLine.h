/**
 * @file   CommandLine.h
 * @brief  コマンドライン引数
 * @author kyo
 * @date   2015/05/24
 */
#ifndef CNVMSG_COMMANDLINE_H_
#define CNVMSG_COMMANDLINE_H_

#include "Common.h"
#include <memory>
#include <vector>
#include <string>

/** Convert MessagePack */
namespace cnvmsg
{
/**
 * コマンドライン引数
 */
class CommandLine
{
public:
  /** モードフラグ */
  enum MODE_FLAG
  {
    JSON_TO_MESSAGEPACK, //!< JSONからMessagePackへの変換を行う
    MESSAGEPACK_TO_JSON  //!< MessagePackからJSONへの変換を行う
  };

private:
  //! Pimplイディオム
  class Impl;
  std::unique_ptr<Impl> m_impl;

private:
  //! コピー防止
  DISALLOW_COPY_AND_ASSIGN(CommandLine);

public:
  /** コンストラクタ */
  CommandLine();

  /** 仮想デストラクタ */
  virtual ~CommandLine();

  /**
   * コマンドライン引数の読み込み
   * @param[in] argc argvの配列サイズ
   * @param[in] argv コマンドライン引数
   */
  void Read(int argc, const char* const argv[]);

  /**
   * モードフラグの取得
   * @return モードフラグ
   */
  MODE_FLAG Mode() const;

  /**
   * 入力ファイルパスの取得
   * @return 入力ファイルパス(Read結果)
   */
  const std::string& InputFile() const;

  /**
   * 出力ファイルパスの取得
   * @return 出力ファイルパス(Read結果)
   */
  const std::string& OutputFile() const;

  /**
   * 指数形式フラグの取得
   * @return 指数形式フラグ(Read結果)
   */
  bool Scientific() const;

  /**
   * 小数点以下の桁数の取得
   * @return 小数点以下の桁数(Read結果)
   */
  int Precision() const;
};
}
#endif // CNVMSG_COMMANDLINE_H_
