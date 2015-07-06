/**
 * @file   Translator.cpp
 * @brief  JSON-MessagePack変換
 * @author kyo
 * @date   2015/07/06
 */
#include "Translator.h"
#include "CommandLine.h"
#include <Json.h>
#include <JsonParser.h>
#include <MsgpackParser.h>
#include <fstream>
#include <string>
#include <iomanip>

/** Convert MessagePack */
namespace cnvmsg
{
/** コンストラクタ */
Translator::Translator() {}

/** 仮想デストラクタ */
Translator::~Translator() {}

/**
 * 変換
 * @param[in] commandline コマンドライン引数の情報
 * @note わざわざ抽象化するほどでもないのでswitch内に処理を書く <br>
 *       処理が複雑になったら抽象化してファクトリパターンでいく
 */
void Translator::Translate(const CommandLine& command)
{
  // 出力ファイルを開く
  std::ofstream ofs;
  ofs.open(command.OutputFile());

  // モード分岐
  switch (command.Mode())
  {
    case CommandLine::JSON_TO_MESSAGEPACK:
    {
      // 入力ファイルを開く
      std::ifstream ifs;
      ifs.open(command.InputFile());
      // ファイルの内容を取得する
      std::string buf;
      std::string tmp;
      while (std::getline(ifs, tmp)) buf += tmp;
      // パースする
      adlib::JsonParser parser;
      const auto& json = parser.Parse(buf);
      // ダンプ
      json.DumpMsgpack(&ofs);
    }
    break;

    case CommandLine::MESSAGEPACK_TO_JSON:
    {
      // 浮動小数点数の形式を指定
      if (command.Scientific())
      {
        ofs << std::scientific;
      }
      else
      {
        ofs << std::fixed;
      }
      // 小数点以下の桁数を指定
      ofs << std::setprecision(command.Precision());
      // 入力ファイルを開く
      std::ifstream ifs;
      ifs.open(command.InputFile(), std::ios::binary);
      // ファイルの内容を取得する
      std::string buf;
      std::string tmp;
      while (std::getline(ifs, tmp)) buf += tmp;
      // パースする
      adlib::MsgpackParser parser;
      const auto& json = parser.Parse(buf);
      // ダンプ
      json.Dump(&ofs);
    }
    break;

    default:
      throw "Program Error";
  }
}
}
