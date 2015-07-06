/**
 * @file   Translator.h
 * @brief  JSON-MessagePack�ϊ�
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
 * JSON-MessagePack�ϊ�
 */
class Translator
{
private:
  //! �R�s�[�h�~
  DISALLOW_COPY_AND_ASSIGN(Translator);

public:
  /** �R���X�g���N�^ */
  Translator();

  /** ���z�f�X�g���N�^ */
  virtual ~Translator();

  /**
   * �ϊ�
   * @param[in] commandline �R�}���h���C�������̏��
   */
  void Translate(const CommandLine& command);
};
}
#endif // CNVMSG_TRANSLATOR_H_
