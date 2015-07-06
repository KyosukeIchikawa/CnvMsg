/**
 * @file   CommandLine.h
 * @brief  �R�}���h���C������
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
 * �R�}���h���C������
 */
class CommandLine
{
public:
  /** ���[�h�t���O */
  enum MODE_FLAG
  {
    JSON_TO_MESSAGEPACK, //!< JSON����MessagePack�ւ̕ϊ����s��
    MESSAGEPACK_TO_JSON  //!< MessagePack����JSON�ւ̕ϊ����s��
  };

private:
  //! Pimpl�C�f�B�I��
  class Impl;
  std::unique_ptr<Impl> m_impl;

private:
  //! �R�s�[�h�~
  DISALLOW_COPY_AND_ASSIGN(CommandLine);

public:
  /** �R���X�g���N�^ */
  CommandLine();

  /** ���z�f�X�g���N�^ */
  virtual ~CommandLine();

  /**
   * �R�}���h���C�������̓ǂݍ���
   * @param[in] argc argv�̔z��T�C�Y
   * @param[in] argv �R�}���h���C������
   */
  void Read(int argc, const char* const argv[]);

  /**
   * ���[�h�t���O�̎擾
   * @return ���[�h�t���O
   */
  MODE_FLAG Mode() const;

  /**
   * ���̓t�@�C���p�X�̎擾
   * @return ���̓t�@�C���p�X(Read����)
   */
  const std::string& InputFile() const;

  /**
   * �o�̓t�@�C���p�X�̎擾
   * @return �o�̓t�@�C���p�X(Read����)
   */
  const std::string& OutputFile() const;

  /**
   * �w���`���t���O�̎擾
   * @return �w���`���t���O(Read����)
   */
  bool Scientific() const;

  /**
   * �����_�ȉ��̌����̎擾
   * @return �����_�ȉ��̌���(Read����)
   */
  int Precision() const;
};
}
#endif // CNVMSG_COMMANDLINE_H_
