/**
 * @file   Common.h
 * @brief  一般定義
 * @author kyo
 * @date   2015/04/05
 */
#ifndef CNVMSG_COMMON_H_
#define CNVMSG_COMMON_H_

/** Convert MessagePack */
namespace cnvmsg
{
//------------------------------------------------------------------------------
// define
//------------------------------------------------------------------------------
//! コピー防止マクロ(privateで使用する)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

//------------------------------------------------------------------------------
// enum
//------------------------------------------------------------------------------
//! 終了コード
enum EXIT_CODE
{
  FAILURE = -1,
  SUCCESS = 0
};
}

#endif  // CNVMSG_COMMON_H_
