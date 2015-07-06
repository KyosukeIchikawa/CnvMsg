/**
 * @file   Msg.h
 * @brief  メッセージ定義
 * @author kyo
 * @date   2015/05/24
 */
#ifndef MPSDRIVE_MSG_H_
#define MPSDRIVE_MSG_H_

#include "Common.h"
#include <string>

/** Convert MessagePack */
namespace cnvmsg
{
/**
 * メッセージ定義
 */
namespace msg
{
/**
 * コマンドライン ヘルプ表記
 */
namespace cmdhelp
{
//! ファイルのパス
static const std::string FILE("入力ファイルのパス, 出力ファイルのパス");
//! ヘルプの表示
static const std::string HELP("ヘルプの表示");
//! モードの指定
static const std::string MODE("モードの指定 (pack: JSON to MessagePack, unpack: MessagePack to JSON)");
//! 指数形式フラグ
static const std::string SCIENTIFIC("JSON出力時の浮動小数点数を指数形式にするフラグ");
//! 小数点以下の桁数
static const std::string PRECISION("JSON出力時の浮動小数点数の小数点以下の桁数");
};
}

}
#endif // MPSDRIVE_MSG_H_
