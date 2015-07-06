/**
 * @file   CommandLine.cpp
 * @brief  コマンドライン引数
 * @author kyo
 * @date   2015/05/24
 */
#include "CommandLine.h"
#include "Msg.h"
#include <CommandLineSetting.h> // Analysis Drive
#include <CommandLineParser.h>  // Analysis Drive
#include <Command.h>            // Analysis Drive
#include <assert.h>
#include <memory>
#include <iostream>
#include <vector>
#include <cstdio>

/** Convert MessagePack */
namespace cnvmsg
{
//! Pimplイディオム
class CommandLine::Impl
{
public:
  /** Prefix */
  class Prefix
  {
  public:
    //! ファイルの指定(接頭辞無し)
    static const std::string FILE;
    //! ヘルプ表示
    static const std::string HELP;
    //! モードの指定
    static const std::string MODE;
    //! 指数形式フラグ
    static const std::string SCIENTIFIC;
    //! 小数点以下の桁数
    static const std::string PRECISION;
  };

  /** デフォルト値 */
  class Default
  {
  public:
    //! モードの指定
    static const CommandLine::MODE_FLAG MODE;
    //! 指数形式フラグ
    static const bool SCIENTIFIC;
    //! 小数点以下の桁数
    static const int PRECISION;
  };

  /** 後続引数の数 */
  class NumberOfParameter
  {
  public:
    //! ファイルの指定(接頭辞無し)
    static const int FILE;
    //! ヘルプ表示
    static const int HELP;
    //! モードの指定
    static const int MODE;
    //! 指数形式フラグ
    static const int SCIENTIFIC;
    //! 小数点以下の桁数
    static const int PRECISION;
  };

  /** モードの指定 選択肢 */
  class SelectMode
  {
  public:
    //! JSONからMessagePackへの変換を行う
    static const std::string JSON_TO_MESSAGEPACK;
    //! MessagePackからJSONへの変換を行う
    static const std::string MESSAGEPACK_TO_JSON;
  };

  //! モード
  CommandLine::MODE_FLAG m_mode;
  //! 指数形式フラグ
  bool m_scientific;
  //! 小数点以下の桁数
  int m_precision;
  //! 入力ファイルパス
  std::string m_inputFilepath;
  //! 出力ファイルパス
  std::string m_outputFilepath;

  /**
   * コンストラクタ
   * @remarks デフォルト値をセットする
   */
  Impl()
    :m_mode(Default::MODE),
    m_scientific(Default::SCIENTIFIC),
    m_precision(Default::PRECISION),
    m_inputFilepath(""),
    m_outputFilepath("")
  {
  }

  /**
   * "/?"の処理(ヘルプの表示)
   * @param[in] settings コマンドライン引数の定義
   */
  void ProcessHelp(const std::vector<adlib::CommandLineSetting>& settings) const
  {
    // ヘルプの表示
    adlib::CommandLineSetting::ShowHelp(settings, msg::cmdhelp::FILE, &std::cout);
  }

  /**
   * ""の処理(ファイル名の取得)
   * @param[in] args ""後続の引数コンテナ
   */
  void ProcessNoPrefix(const std::vector<std::string>& args)
  {
    // 後続引数の数が0未満であればプログラムエラー
    assert(args.size() > 0);

    // 後続引数の数が規定の数でなければエラー
    if (args.size() != Impl::NumberOfParameter::FILE)
    {
      // エラーを投げる
      throw "There is not two File Names.";
    }
    //----- 入出力ファイル名を取得 -----//
    m_inputFilepath = args.at(0);
    m_outputFilepath = args.at(1);
  }

  /**
   * "/mode"の処理(モードの指定)
   * @param[in] args "/mode"後続の引数コンテナ
   */
  void ProcessMode(const std::vector<std::string>& args)
  {
    // 後続引数の数が0以下であればプログラムエラー
    assert(args.size() > 0);

    //----- モードを取得 -----//
    if (args.at(0) == Impl::SelectMode::JSON_TO_MESSAGEPACK)
    {
      // JSONからMessagePackへの変換を行う
      m_mode = MODE_FLAG::JSON_TO_MESSAGEPACK;
    }
    else if (args.at(0) == Impl::SelectMode::MESSAGEPACK_TO_JSON)
    {
      // MessagePackからJSONへの変換を行う
      m_mode = MODE_FLAG::MESSAGEPACK_TO_JSON;
    }
    else
    {
      // エラーを投げる
      throw "Unknown Mode.";
    }
  }

  /**
   * "/s"の処理(指数形式フラグ)
   * @param[in] args "/s"後続の引数コンテナ
   */
  void ProcessScientific(const std::vector<std::string>& args)
  {
    m_scientific = true;
  }

  /**
   * "/precision"の処理(小数点以下の桁数)
   * @param[in] args "/precision"後続の引数コンテナ
   */
  void ProcessPrecision(const std::vector<std::string>& args)
  {
    // 後続引数の数が0以下であればプログラムエラー
    assert(args.size() > 0);

    //----- 小数点以下の桁数を取得 -----//
    m_precision = atoi(args.at(0).c_str());
  }
};

//! Prefix --- ファイルの指定(接頭辞無し)
const std::string CommandLine::Impl::Prefix::FILE("");
//! Prefix --- ヘルプ表示
const std::string CommandLine::Impl::Prefix::HELP("/?");
//! Prefix --- モードの指定
const std::string CommandLine::Impl::Prefix::MODE("/mode");
//! Prefix --- 指数形式フラグ
const std::string CommandLine::Impl::Prefix::SCIENTIFIC("/s");
//! Prefix --- 小数点以下の桁数
const std::string CommandLine::Impl::Prefix::PRECISION("/precision");

//! デフォルト値 --- モードの指定
const CommandLine::MODE_FLAG CommandLine::Impl::Default::MODE(MODE_FLAG::JSON_TO_MESSAGEPACK);
//! デフォルト値 --- 指数形式フラグ
const bool CommandLine::Impl::Default::SCIENTIFIC(false);
//! デフォルト値 --- 小数点以下の桁数
const int CommandLine::Impl::Default::PRECISION(3);

//! 後続引数の数 --- ファイルの指定(接頭辞無し)
const int CommandLine::Impl::NumberOfParameter::FILE(2);
//! 後続引数の数 --- ヘルプ表示
const int CommandLine::Impl::NumberOfParameter::HELP(0);
//! 後続引数の数 --- モードの指定
const int CommandLine::Impl::NumberOfParameter::MODE(1);
//! 後続引数の数 --- 指数形式フラグ
const int CommandLine::Impl::NumberOfParameter::SCIENTIFIC(0);
//! 後続引数の数 --- 小数点以下の桁数
const int CommandLine::Impl::NumberOfParameter::PRECISION(1);

//! JSONからMessagePackへの変換を行う
const std::string CommandLine::Impl::SelectMode::JSON_TO_MESSAGEPACK("pack");
//! MessagePackからJSONへの変換を行う
const std::string CommandLine::Impl::SelectMode::MESSAGEPACK_TO_JSON("unpack");

/**
 * コマンドライン引数の読み込み
 * @param[in] argc argvの配列サイズ
 * @param[in] argv コマンドライン引数
 */
void CommandLine::Read(int argc, const char* const argv[])
{
  // 前回のRead結果を初期化
  m_impl = std::make_unique<Impl>();

  // コマンドライン引数の定義
  // ※ コマンドライン引数の種類が追加された場合はここも更新
  std::vector<adlib::CommandLineSetting> settings
  {
    adlib::CommandLineSetting(Impl::Prefix::HELP, Impl::NumberOfParameter::HELP, msg::cmdhelp::HELP),
    adlib::CommandLineSetting(Impl::Prefix::MODE, Impl::NumberOfParameter::MODE, msg::cmdhelp::MODE),
    adlib::CommandLineSetting(Impl::Prefix::SCIENTIFIC, Impl::NumberOfParameter::SCIENTIFIC, msg::cmdhelp::SCIENTIFIC),
    adlib::CommandLineSetting(Impl::Prefix::PRECISION, Impl::NumberOfParameter::PRECISION, msg::cmdhelp::PRECISION)
  };

  //----- コマンドライン引数をパースする -----//
  adlib::CommandLineParser parser;
  auto command = parser.Parse(settings, argc, argv);
  // エラーチェック
  if (parser.ErrorMessage().size() > 0)
  {
    throw "CommandLine Error";
  }

  //----- ヘルプ表示(引数が入力されなかった場合も行う) -----//
  if ((command.size() <= 1) || (command.count(Impl::Prefix::HELP) > 0))
  {
    m_impl->ProcessHelp(settings);
    // 正常終了
    exit(EXIT_CODE::SUCCESS);
  }

  //----- ファイル名 -----//
  if (command.count(Impl::Prefix::FILE) > 0)
  {
    m_impl->ProcessNoPrefix(command[Impl::Prefix::FILE].Args());
  }
  else
  {
    // 取得できない場合はエラーを投げる
    throw "There is no File Name.";
  }

  //----- モード -----//
  if (command.count(Impl::Prefix::MODE) > 0)
  {
    m_impl->ProcessMode(command[Impl::Prefix::MODE].Args());
  }

  //----- 指数形式フラグ -----//
  if (command.count(Impl::Prefix::SCIENTIFIC) > 0)
  {
    m_impl->ProcessScientific(command[Impl::Prefix::SCIENTIFIC].Args());
  }

  //----- 小数点以下の桁数 -----//
  if (command.count(Impl::Prefix::PRECISION) > 0)
  {
    m_impl->ProcessPrecision(command[Impl::Prefix::PRECISION].Args());
  }
}

/** コンストラクタ */
CommandLine::CommandLine() :m_impl(std::make_unique<Impl>()) {}

/** 仮想デストラクタ */
CommandLine::~CommandLine() {}

/**
 * モードフラグの取得
 * @return モードフラグ
 */
CommandLine::MODE_FLAG CommandLine::Mode() const
{
  return m_impl->m_mode;
}

/**
 * 入力ファイルパスの取得
 * @return 入力ファイルパス(Read結果)
 */
const std::string& CommandLine::InputFile() const
{
  return m_impl->m_inputFilepath;
}

/**
 * 出力ファイルパスの取得
 * @return 出力ファイルパス(Read結果)
 */
const std::string& CommandLine::OutputFile() const
{
  return m_impl->m_outputFilepath;
}

/**
 * 指数形式フラグの取得
 * @return 指数形式フラグ(Read結果)
 */
bool CommandLine::Scientific() const
{
  return m_impl->m_scientific;
}

/**
 * 小数点以下の桁数の取得
 * @return 小数点以下の桁数(Read結果)
 */
int CommandLine::Precision() const
{
  return m_impl->m_precision;
}
}
