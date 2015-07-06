/**
 * @file   Main.cpp
 * @brief  CnvMsg Entry Point
 * @author kyo
 * @date   2015/03/14
 */
#include "Common.h"
#include "CommandLine.h"
#include "Translator.h"
#include <AnalysisDrive.h> // Analysis Drive
#include <iostream>

/**
 * メイン関数
 * @param[in] argc argvの配列サイズ
 * @param[in] argv コマンドライン引数
 * @return プログラムの終了コード
 */
int main(int argc, char* argv[])
{
  try
  {
    // コマンドライン引数の読み込み
    cnvmsg::CommandLine commandLine;
    commandLine.Read(argc, argv);

    // 変換
    cnvmsg::Translator translator;
    translator.Translate(commandLine);
  }
  catch (const std::string& err)
  {
    std::cout << err << std::endl;
  }
  catch (const char* err)
  {
    std::cout << err << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown Error." << std::endl;
    // プログラムエラー(想定外のエラー)
    return cnvmsg::EXIT_CODE::FAILURE;
  }

  return cnvmsg::EXIT_CODE::SUCCESS;
}
