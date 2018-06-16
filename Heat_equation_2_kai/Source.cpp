#include<iostream>
#include<vector>

static double k = 0.467; //�����̔M�`����(�����l���萔)  �Q�l�����@https://www.jstage.jst.go.jp/article/nskkk1995/43/4/43_4_368/_pdf�@3�y�[�W��
static double a = 0.00000013; //�����̔M�g�U��(�����l���萔)�@�Q�l�����@https://www.jstage.jst.go.jp/article/jhej1987/50/2/50_2_147/_pdf�@3�y�[�W��
static double h = 20;//��C�̑Η��M�`�B��
static double dx = 0.002;//��ԍ���
static double dy = 0.002;//��ԍ���
static double dt = 2;//���ԍ���
static double lim_t = 1000;//�ő厞��
static double x0_ = 200;//x=0(x���̓S�̉��x)
static double y0_ = 200;//y=0(y���̓S�̉��x)�@//�Ȃ񂩌������ɒu�������������͓S���Ƃ��āAy���ǂȂ�ł����S�ƕǂɂ������Ă��Ԃ��ĕςȊ����Ȃ̂Ō�łȂ񂩕ς��܂�
static double air_T = 25;//��C�̉��x
static double meat_T = 10;//�����̓��̉��x

int main() {

	double x;//���@//�����ł����l��Width��Height���ƒ����Ŕ��肸�炢�̂�(z�g�����܂�)
	double y;//�c�@

	std::cout << "�c�̒�������͂��Ă�������[cm]" << std::endl;
	std::cin >> y;
	std::cout << "���̒�������͂��Ă�������[cm]" << std::endl;
	std::cin >> x;

	x = x / 100.0;//���̌�����[m]�ɕϊ�
	y = y / 100.0;

	int t_num = int(lim_t / dt) + 3;//���ԕ����� ���Ԃ𒲐����邽��
	int x_num = int(x / dx) + 2; //��ԕ����� �S��x=0 x=[max]����C�Ƃ��邽��+2
	int y_num = int(y / dy) + 2; //��ԕ����� �S��y=0 y=[max]����C�Ƃ��邽��+2

	std::vector<std::vector<std::vector<double>>> T; //T[����t][�ꏊx][�ꏊy]
	T = std::vector<std::vector<std::vector<double>>>(t_num, std::vector<std::vector<double>>(x_num, std::vector<double>(y_num, meat_T))); //�S�Ă̎��Ԃ̉��x�Əꏊ�������̓��̉��x�ŏ�����

	std::vector<std::vector<std::vector<double>>> T_(T);//�R�s�[�R���X�g���N�^�@�s�� T �ƑS����������(�΂߂̌v�Z�̂��߂ɂ�����i�[����s�����肽������)


	for (int t = 2; t < t_num; t++) {

		for (int x = 0; x < x_num; x++) {                   //T��T_�ł���Ă邱�Ƃ͓���
			T[0][x][0] = x0_;//����=0�̎�
			T_[0][x][0] = x0_;//����=0�̎�

			T[t - 1][x][0] = x0_;//x�ɂ��Ă̑�1�틫�E����
								 //��ԍ��ǂ̉��x��x0_=200��

			T[t - 1][x][y_num - 1] = (h * dx*air_T + k * T[t - 1][x][y_num - 2]) / (h*dx + k); //x�ɂ��Ă̑�3�틫�E����
																							   //  ���̕\�ʉ��x        �@�@�@��C�̉��x�@�@�@1�O�̓��̉��x�@�@�@�@�@�@�@�@�@�@


			T_[t - 1][x][0] = x0_;//x�ɂ��Ă̑�1�틫�E����
			T_[t - 1][x][y_num - 1] = (h * dx*air_T + k * T_[t - 1][x][y_num - 2]) / (h*dx + k); //x�ɂ��Ă̑�3�틫�E����
		}

		for (int y = 0; y < y_num; y++) {                  //T��T_�ł���Ă邱�Ƃ͓���
			T[0][0][y] = y0_;//����=0�̎�
			T_[0][0][y] = y0_;//����=0�̎�

			T[t - 1][0][y] = y0_;//y�ɂ��Ă̑�1�틫�E����
								 //��ԏ�ǂ̉��x��y0_=200��

			T[t - 1][x_num - 1][y] = (h * dy * air_T + k * T[t - 1][x_num - 2][y]) / (h*dy + k); //y�ɂ��Ă̑�3�틫�E����
																								 //  ���̕\�ʉ��x        �@�@�@��C�̉��x�@�@�@1�O�̓��̉��x�@�@

			T_[t - 1][0][y] = y0_;//y�ɂ��Ă̑�1�틫�E����
			T_[t - 1][x_num - 1][y] = (h * dy * air_T + k * T_[t - 1][x_num - 2][y]) / (h*dy + k); //y�ɂ��Ă̑�3�틫�E����
		}


		for (int x = 0; x < x_num - 2; x++) {
			for (int y = 0; y < y_num - 2; y++) {
				//�M�`��������
				//�㉺���E�̂S���l�������ꍇ�̂݁@�΂߂̔M�̓����͌v�Z���ĂȂ�
				T[t][x + 1][y + 1] = a * dt*(T[t - 1][x][y + 1] + T[t - 1][x + 1][y] + T[t - 1][x + 1][y + 2] + T[t - 1][x + 2][y + 1] - 4 * T[t - 1][x + 1][y + 1]) / dx / dx + T[t - 1][x + 1][y + 1]; //�g�U������(�M�`��������)�@      �Ƃ肠�������ʂ̍����@(�I�C���[�⃋���Q�N�b�^�ł����Ɛ��m�ɂł�����(�H)
				 //�@���Ԉ�O�̑���ʒu�@�@�@           �E�ׁ@                  ��ׁ@�@�@�@�@�@�@�@�@���ׁ@�@�@�@�@�@�@�@�@���ׁ@�@�@�@�@�@�@�@�@�@�@�@����ʒu�@�@�@�@�@�@�@�@�@�@����ʒu


																																																		 //�M�`��������
																																																		 //�㉺���E���u�S�΂ߕ����v���l��
				T_[t][x + 1][y + 1] = a * dt*(T_[t - 1][x][y] + T_[t - 1][x][y + 1] + T_[t - 1][x][y + 2] + T_[t - 1][x + 1][y] + T_[t - 1][x + 1][y + 2] + T_[t - 1][x + 2][y] + T_[t - 1][x + 2][y + 1] + T_[t - 1][x + 2][y + 2] - 4 * T_[t - 1][x + 1][y + 1]) / dx / dx + T_[t - 1][x + 1][y + 1];  //�g�U������(�M�`��������)�@      �Ƃ肠�������ʂ̍����@(�I�C���[�⃋���Q�N�b�^�ł����Ɛ��m�ɂł�����(�H))
				//�@���Ԉ�O�̑���ʒu�@�@�@              �E��	�@    �@�@�@�@�E�ׁ@�@�@�@�@ �@�@�@�E��                   ��ׁ@�@�@�@�@�@�@  �@���ׁ@�@�@�@    �@         ����@�@�@�@         ���ׁ@                     �����@�@�@�@�@�@   �@�@�@   ����ʒu�@�@�@�@�@�@   �@�@     �@�@����ʒu	


			}
		}
	}



	double time = 0;

	for (int i = 0; i < t_num - 2; i++) {  //��������T�̏o��
		std::cout << time << "[s] " << std::endl; //�����Ԃ̏o��

		for (int j = 0; j < x_num; j++) {
			for (int k = 0; k < y_num; k++) {

				std::cout << T[i][j][k] << " ";  //���ׂĂ̎��ԂƂ��ׂĂ̏ꏊ���L�^����Ă���3�����s��@T[����][�ꏊx][�ꏊy]�@�̌��ʏo��		
			}
			std::cout << std::endl;  //1�񂲂Ƃɉ��s

		}
		std::cout << std::endl;  //1�񂲂Ƃɉ��s
		time = time + dt; //���Ԃ������Ԃɒ����ďo��
	}

	time = 0;



	for (int i = 0; i < t_num - 2; i++) {  //��������T_�̏o��
		std::cout << time << "[s] " << std::endl; //�����Ԃ̏o��

		for (int j = 0; j < x_num; j++) {
			for (int k = 0; k < y_num; k++) {

				std::cout << T_[i][j][k] << " ";  //���ׂĂ̎��ԂƂ��ׂĂ̏ꏊ���L�^����Ă���2�����s��@T_[����][�ꏊx][�ꏊy]�@�̌��ʏo��		
			}
			std::cout << std::endl;  //1�񂲂Ƃɉ��s

		}
		time = time + dt; //���Ԃ������Ԃɒ����ďo��
	}


	return 0;
}