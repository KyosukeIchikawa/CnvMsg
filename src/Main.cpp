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
 * ���C���֐�
 * @param[in] argc argv�̔z��T�C�Y
 * @param[in] argv �R�}���h���C������
 * @return �v���O�����̏I���R�[�h
 */
int main(int argc, char* argv[])
{
  try
  {
    // �R�}���h���C�������̓ǂݍ���
    cnvmsg::CommandLine commandLine;
    commandLine.Read(argc, argv);

    // �ϊ�
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
    // �v���O�����G���[(�z��O�̃G���[)
    return cnvmsg::EXIT_CODE::FAILURE;
  }

  return cnvmsg::EXIT_CODE::SUCCESS;
}
