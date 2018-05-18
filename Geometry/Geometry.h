#pragma once
#include <cmath>
#include <glm\glm.hpp>
#include <iostream>

namespace Geometry
{
	// ���Ƿ���ֱ����
	bool inSameLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p);

	// ���Ƿ����߶���
	bool inSameSegment(glm::vec3 p1, glm::vec3 p2, glm::vec3 p);

	// ���Ƿ�����������
	bool inSameTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p);

	// �㵽ֱ�ߵľ���
	float distance2Line(glm::vec3 p1, glm::vec3 p2, glm::vec3 p);

	// �㵽�߶εľ���
	float distance2Segment(glm::vec3 p1, glm::vec3 p2, glm::vec3 p);

	// �㵽�����εľ���
	float distance2Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p);

	// �Ƿ񹹳�������
	bool isTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
}