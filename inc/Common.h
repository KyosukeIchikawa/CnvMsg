/**
 * @file   Common.h
 * @brief  ��ʒ�`
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
//! �R�s�[�h�~�}�N��(private�Ŏg�p����)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

//------------------------------------------------------------------------------
// enum
//------------------------------------------------------------------------------
//! �I���R�[�h
enum EXIT_CODE
{
  FAILURE = -1,
  SUCCESS = 0
};
}

#endif  // CNVMSG_COMMON_H_
