/**
 * @file   CommandLine.cpp
 * @brief  �R�}���h���C������
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
//! Pimpl�C�f�B�I��
class CommandLine::Impl
{
public:
  /** Prefix */
  class Prefix
  {
  public:
    //! �t�@�C���̎w��(�ړ�������)
    static const std::string FILE;
    //! �w���v�\��
    static const std::string HELP;
    //! ���[�h�̎w��
    static const std::string MODE;
    //! �w���`���t���O
    static const std::string SCIENTIFIC;
    //! �����_�ȉ��̌���
    static const std::string PRECISION;
  };

  /** �f�t�H���g�l */
  class Default
  {
  public:
    //! ���[�h�̎w��
    static const CommandLine::MODE_FLAG MODE;
    //! �w���`���t���O
    static const bool SCIENTIFIC;
    //! �����_�ȉ��̌���
    static const int PRECISION;
  };

  /** �㑱�����̐� */
  class NumberOfParameter
  {
  public:
    //! �t�@�C���̎w��(�ړ�������)
    static const int FILE;
    //! �w���v�\��
    static const int HELP;
    //! ���[�h�̎w��
    static const int MODE;
    //! �w���`���t���O
    static const int SCIENTIFIC;
    //! �����_�ȉ��̌���
    static const int PRECISION;
  };

  /** ���[�h�̎w�� �I���� */
  class SelectMode
  {
  public:
    //! JSON����MessagePack�ւ̕ϊ����s��
    static const std::string JSON_TO_MESSAGEPACK;
    //! MessagePack����JSON�ւ̕ϊ����s��
    static const std::string MESSAGEPACK_TO_JSON;
  };

  //! ���[�h
  CommandLine::MODE_FLAG m_mode;
  //! �w���`���t���O
  bool m_scientific;
  //! �����_�ȉ��̌���
  int m_precision;
  //! ���̓t�@�C���p�X
  std::string m_inputFilepath;
  //! �o�̓t�@�C���p�X
  std::string m_outputFilepath;

  /**
   * �R���X�g���N�^
   * @remarks �f�t�H���g�l���Z�b�g����
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
   * "/?"�̏���(�w���v�̕\��)
   * @param[in] settings �R�}���h���C�������̒�`
   */
  void ProcessHelp(const std::vector<adlib::CommandLineSetting>& settings) const
  {
    // �w���v�̕\��
    adlib::CommandLineSetting::ShowHelp(settings, msg::cmdhelp::FILE, &std::cout);
  }

  /**
   * ""�̏���(�t�@�C�����̎擾)
   * @param[in] args ""�㑱�̈����R���e�i
   */
  void ProcessNoPrefix(const std::vector<std::string>& args)
  {
    // �㑱�����̐���0�����ł���΃v���O�����G���[
    assert(args.size() > 0);

    // �㑱�����̐����K��̐��łȂ���΃G���[
    if (args.size() != Impl::NumberOfParameter::FILE)
    {
      // �G���[�𓊂���
      throw "There is not two File Names.";
    }
    //----- ���o�̓t�@�C�������擾 -----//
    m_inputFilepath = args.at(0);
    m_outputFilepath = args.at(1);
  }

  /**
   * "/mode"�̏���(���[�h�̎w��)
   * @param[in] args "/mode"�㑱�̈����R���e�i
   */
  void ProcessMode(const std::vector<std::string>& args)
  {
    // �㑱�����̐���0�ȉ��ł���΃v���O�����G���[
    assert(args.size() > 0);

    //----- ���[�h���擾 -----//
    if (args.at(0) == Impl::SelectMode::JSON_TO_MESSAGEPACK)
    {
      // JSON����MessagePack�ւ̕ϊ����s��
      m_mode = MODE_FLAG::JSON_TO_MESSAGEPACK;
    }
    else if (args.at(0) == Impl::SelectMode::MESSAGEPACK_TO_JSON)
    {
      // MessagePack����JSON�ւ̕ϊ����s��
      m_mode = MODE_FLAG::MESSAGEPACK_TO_JSON;
    }
    else
    {
      // �G���[�𓊂���
      throw "Unknown Mode.";
    }
  }

  /**
   * "/s"�̏���(�w���`���t���O)
   * @param[in] args "/s"�㑱�̈����R���e�i
   */
  void ProcessScientific(const std::vector<std::string>& args)
  {
    m_scientific = true;
  }

  /**
   * "/precision"�̏���(�����_�ȉ��̌���)
   * @param[in] args "/precision"�㑱�̈����R���e�i
   */
  void ProcessPrecision(const std::vector<std::string>& args)
  {
    // �㑱�����̐���0�ȉ��ł���΃v���O�����G���[
    assert(args.size() > 0);

    //----- �����_�ȉ��̌������擾 -----//
    m_precision = atoi(args.at(0).c_str());
  }
};

//! Prefix --- �t�@�C���̎w��(�ړ�������)
const std::string CommandLine::Impl::Prefix::FILE("");
//! Prefix --- �w���v�\��
const std::string CommandLine::Impl::Prefix::HELP("/?");
//! Prefix --- ���[�h�̎w��
const std::string CommandLine::Impl::Prefix::MODE("/mode");
//! Prefix --- �w���`���t���O
const std::string CommandLine::Impl::Prefix::SCIENTIFIC("/s");
//! Prefix --- �����_�ȉ��̌���
const std::string CommandLine::Impl::Prefix::PRECISION("/precision");

//! �f�t�H���g�l --- ���[�h�̎w��
const CommandLine::MODE_FLAG CommandLine::Impl::Default::MODE(MODE_FLAG::JSON_TO_MESSAGEPACK);
//! �f�t�H���g�l --- �w���`���t���O
const bool CommandLine::Impl::Default::SCIENTIFIC(false);
//! �f�t�H���g�l --- �����_�ȉ��̌���
const int CommandLine::Impl::Default::PRECISION(3);

//! �㑱�����̐� --- �t�@�C���̎w��(�ړ�������)
const int CommandLine::Impl::NumberOfParameter::FILE(2);
//! �㑱�����̐� --- �w���v�\��
const int CommandLine::Impl::NumberOfParameter::HELP(0);
//! �㑱�����̐� --- ���[�h�̎w��
const int CommandLine::Impl::NumberOfParameter::MODE(1);
//! �㑱�����̐� --- �w���`���t���O
const int CommandLine::Impl::NumberOfParameter::SCIENTIFIC(0);
//! �㑱�����̐� --- �����_�ȉ��̌���
const int CommandLine::Impl::NumberOfParameter::PRECISION(1);

//! JSON����MessagePack�ւ̕ϊ����s��
const std::string CommandLine::Impl::SelectMode::JSON_TO_MESSAGEPACK("pack");
//! MessagePack����JSON�ւ̕ϊ����s��
const std::string CommandLine::Impl::SelectMode::MESSAGEPACK_TO_JSON("unpack");

/**
 * �R�}���h���C�������̓ǂݍ���
 * @param[in] argc argv�̔z��T�C�Y
 * @param[in] argv �R�}���h���C������
 */
void CommandLine::Read(int argc, const char* const argv[])
{
  // �O���Read���ʂ�������
  m_impl = std::make_unique<Impl>();

  // �R�}���h���C�������̒�`
  // �� �R�}���h���C�������̎�ނ��ǉ����ꂽ�ꍇ�͂������X�V
  std::vector<adlib::CommandLineSetting> settings
  {
    adlib::CommandLineSetting(Impl::Prefix::HELP, Impl::NumberOfParameter::HELP, msg::cmdhelp::HELP),
    adlib::CommandLineSetting(Impl::Prefix::MODE, Impl::NumberOfParameter::MODE, msg::cmdhelp::MODE),
    adlib::CommandLineSetting(Impl::Prefix::SCIENTIFIC, Impl::NumberOfParameter::SCIENTIFIC, msg::cmdhelp::SCIENTIFIC),
    adlib::CommandLineSetting(Impl::Prefix::PRECISION, Impl::NumberOfParameter::PRECISION, msg::cmdhelp::PRECISION)
  };

  //----- �R�}���h���C���������p�[�X���� -----//
  adlib::CommandLineParser parser;
  auto command = parser.Parse(settings, argc, argv);
  // �G���[�`�F�b�N
  if (parser.ErrorMessage().size() > 0)
  {
    throw "CommandLine Error";
  }

  //----- �w���v�\��(���������͂���Ȃ������ꍇ���s��) -----//
  if ((command.size() <= 1) || (command.count(Impl::Prefix::HELP) > 0))
  {
    m_impl->ProcessHelp(settings);
    // ����I��
    exit(EXIT_CODE::SUCCESS);
  }

  //----- �t�@�C���� -----//
  if (command.count(Impl::Prefix::FILE) > 0)
  {
    m_impl->ProcessNoPrefix(command[Impl::Prefix::FILE].Args());
  }
  else
  {
    // �擾�ł��Ȃ��ꍇ�̓G���[�𓊂���
    throw "There is no File Name.";
  }

  //----- ���[�h -----//
  if (command.count(Impl::Prefix::MODE) > 0)
  {
    m_impl->ProcessMode(command[Impl::Prefix::MODE].Args());
  }

  //----- �w���`���t���O -----//
  if (command.count(Impl::Prefix::SCIENTIFIC) > 0)
  {
    m_impl->ProcessScientific(command[Impl::Prefix::SCIENTIFIC].Args());
  }

  //----- �����_�ȉ��̌��� -----//
  if (command.count(Impl::Prefix::PRECISION) > 0)
  {
    m_impl->ProcessPrecision(command[Impl::Prefix::PRECISION].Args());
  }
}

/** �R���X�g���N�^ */
CommandLine::CommandLine() :m_impl(std::make_unique<Impl>()) {}

/** ���z�f�X�g���N�^ */
CommandLine::~CommandLine() {}

/**
 * ���[�h�t���O�̎擾
 * @return ���[�h�t���O
 */
CommandLine::MODE_FLAG CommandLine::Mode() const
{
  return m_impl->m_mode;
}

/**
 * ���̓t�@�C���p�X�̎擾
 * @return ���̓t�@�C���p�X(Read����)
 */
const std::string& CommandLine::InputFile() const
{
  return m_impl->m_inputFilepath;
}

/**
 * �o�̓t�@�C���p�X�̎擾
 * @return �o�̓t�@�C���p�X(Read����)
 */
const std::string& CommandLine::OutputFile() const
{
  return m_impl->m_outputFilepath;
}

/**
 * �w���`���t���O�̎擾
 * @return �w���`���t���O(Read����)
 */
bool CommandLine::Scientific() const
{
  return m_impl->m_scientific;
}

/**
 * �����_�ȉ��̌����̎擾
 * @return �����_�ȉ��̌���(Read����)
 */
int CommandLine::Precision() const
{
  return m_impl->m_precision;
}
}
