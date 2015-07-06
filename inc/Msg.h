/**
 * @file   Msg.h
 * @brief  ���b�Z�[�W��`
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
 * ���b�Z�[�W��`
 */
namespace msg
{
/**
 * �R�}���h���C�� �w���v�\�L
 */
namespace cmdhelp
{
//! �t�@�C���̃p�X
static const std::string FILE("���̓t�@�C���̃p�X, �o�̓t�@�C���̃p�X");
//! �w���v�̕\��
static const std::string HELP("�w���v�̕\��");
//! ���[�h�̎w��
static const std::string MODE("���[�h�̎w�� (pack: JSON to MessagePack, unpack: MessagePack to JSON)");
//! �w���`���t���O
static const std::string SCIENTIFIC("JSON�o�͎��̕��������_�����w���`���ɂ���t���O");
//! �����_�ȉ��̌���
static const std::string PRECISION("JSON�o�͎��̕��������_���̏����_�ȉ��̌���");
};
}

}
#endif // MPSDRIVE_MSG_H_
