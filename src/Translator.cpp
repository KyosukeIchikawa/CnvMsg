/**
 * @file   Translator.cpp
 * @brief  JSON-MessagePack�ϊ�
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
/** �R���X�g���N�^ */
Translator::Translator() {}

/** ���z�f�X�g���N�^ */
Translator::~Translator() {}

/**
 * �ϊ�
 * @param[in] commandline �R�}���h���C�������̏��
 * @note �킴�킴���ۉ�����قǂł��Ȃ��̂�switch���ɏ��������� <br>
 *       ���������G�ɂȂ����璊�ۉ����ăt�@�N�g���p�^�[���ł���
 */
void Translator::Translate(const CommandLine& command)
{
  // �o�̓t�@�C�����J��
  std::ofstream ofs;
  ofs.open(command.OutputFile());

  // ���[�h����
  switch (command.Mode())
  {
    case CommandLine::JSON_TO_MESSAGEPACK:
    {
      // ���̓t�@�C�����J��
      std::ifstream ifs;
      ifs.open(command.InputFile());
      // �t�@�C���̓��e���擾����
      std::string buf;
      std::string tmp;
      while (std::getline(ifs, tmp)) buf += tmp;
      // �p�[�X����
      adlib::JsonParser parser;
      const auto& json = parser.Parse(buf);
      // �_���v
      json.DumpMsgpack(&ofs);
    }
    break;

    case CommandLine::MESSAGEPACK_TO_JSON:
    {
      // ���������_���̌`�����w��
      if (command.Scientific())
      {
        ofs << std::scientific;
      }
      else
      {
        ofs << std::fixed;
      }
      // �����_�ȉ��̌������w��
      ofs << std::setprecision(command.Precision());
      // ���̓t�@�C�����J��
      std::ifstream ifs;
      ifs.open(command.InputFile(), std::ios::binary);
      // �t�@�C���̓��e���擾����
      std::string buf;
      std::string tmp;
      while (std::getline(ifs, tmp)) buf += tmp;
      // �p�[�X����
      adlib::MsgpackParser parser;
      const auto& json = parser.Parse(buf);
      // �_���v
      json.Dump(&ofs);
    }
    break;

    default:
      throw "Program Error";
  }
}
}