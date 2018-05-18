#include "Geometry.h"
#include <algorithm>
using namespace std;

// ���Ƿ���ֱ����
bool Geometry::inSameLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p)
{
	if (glm::distance(p1, p2) < 1e-4)
	{
		if (glm::distance(p, p2) < 1e-4)
			return true;
		return false;
	}
	glm::vec3 CA = p1 - p;
	glm::vec3 CB = p2 - p;
	float area = glm::length(glm::cross(CA, CB));
	if (abs(area) < 1e-4)
		return true;
	return false;
}

// ���Ƿ����߶���
bool Geometry::inSameSegment(glm::vec3 p1, glm::vec3 p2, glm::vec3 p)
{
	if (inSameLine(p1, p2, p))		// ���ȱ�����ͬһ��ֱ����
	{
		bool f1 = (p.x <= p1.x && p.x >= p2.x) || (p.x >= p1.x && p.x <= p2.x);
		bool f2 = (p.y <= p1.y && p.y >= p2.y) || (p.y >= p1.y && p.y <= p2.y);
		bool f3 = (p.z <= p1.z && p.z >= p2.z) || (p.z >= p1.z && p.z <= p2.z);
		if (f1 && f2 &&f3)
			return true;
		return false;
	}
	else
		return false;
}

// ���Ƿ�����������
bool Geometry::inSameTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p)
{
	if (!isTriangle(p1, p2, p3))		// ������������
	{
		return false;
	}
	glm::vec3 AC = p3 - p1;
	glm::vec3 AB = p2 - p1;
	float area = glm::length(glm::cross(AB, AC))/2.0f;
	
	glm::vec3 PA = p1 - p;
	glm::vec3 PB = p2 - p;
	glm::vec3 PC = p3 - p;
	float area_pab = glm::length(glm::cross(PA, PB)) / 2.0f;
	float area_pbc = glm::length(glm::cross(PC, PB)) / 2.0f;
	float area_pac = glm::length(glm::cross(PA, PC)) / 2.0f;
	if (abs(area_pab + area_pac + area_pbc - area) < 1e-3)
		return true;
	return false;
}

// �㵽ֱ�ߵľ���
float Geometry::distance2Line(glm::vec3 p1, glm::vec3 p2, glm::vec3 p)
{
	if (glm::distance(p1, p2) < 1e-4)
		return glm::distance(p1, p);
	float ab = glm::length(p2 - p1);
	glm::vec3 AB = p2 - p1;
	glm::vec3 AP = p - p1;
	float area = glm::length(glm::cross(AB, AP));
	return area / ab;
}

// �㵽�����εľ���
float Geometry::distance2Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p)
{
	if (!isTriangle(p1, p2, p3))
	{
		if (glm::distance(p1, p2) < 1e-4 && glm::distance(p2, p3) < 1e-4)		// ������ͬ
			return glm::distance(p1, p);
		if (glm::distance(p1, p2) < 1e-4)										// �����غ�
			return distance2Segment(p1, p3, p);
		if (glm::distance(p3, p2) < 1e-4)
			return distance2Segment(p1, p3, p);
		if (glm::distance(p3, p1) < 1e-4)
			return distance2Segment(p2, p3, p);
		return min(distance2Segment(p1, p2, p), distance2Segment(p1, p3, p));	// ���㹲��
	}	
	glm::vec3 AB = p2 - p1;							// ����������һ�㣺D = A + t0 * AB + t1 * AC;
	glm::vec3 AC = p3 - p1;			
	float a1 = glm::dot(p - p1, AB);
	float b1 = glm::dot(AB, AB);
	float c1 = glm::dot(AB, AC);
	float a2 = glm::dot(p - p1, AC);
	float b2 = glm::dot(AB, AC);
	float c2 = glm::dot(AC, AC);
	// �������
	float t2 = (a1*b2 - a2*b1) / (b2*c1 - b1*c2);	// �������
	float t1 = (a1*c2 - a2*c1) / (b1*c2 - b2*c1);
	glm::vec3 p4 = p1 + t1*AB + t2*AC;			// �����
	if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1 && t1 + t2 <= 1)	// ����������
		return glm::distance(p4, p);
	float distance_min = min(distance2Segment(p1, p2, p4), min(distance2Segment(p1, p3, p4), distance2Segment(p2, p3, p4)));	// �������ĵ�
	return sqrt(pow(glm::distance(p4, p), 2) + pow(distance_min, 2));
}

// �㵽�߶εľ���
float Geometry::distance2Segment(glm::vec3 p1, glm::vec3 p2, glm::vec3 p)
{
	if (glm::distance(p1, p2) < 1e-4)
		return glm::distance(p1, p);
	if (inSameLine(p1, p2, p))
	{
		if (inSameSegment(p1, p2, p))		// ���߶���
			return 0;
		return min(glm::distance(p, p1), glm::distance(p, p2));
	}
	glm::vec3 AB = p2 - p1;
	glm::vec3 AC = p - p1;
	glm::vec3 BC = p - p2;
	glm::vec3 BA = p1 - p2;
		
	float distance_line = distance2Line(p1, p2, p);	// �㵽ֱ�߾���
	float sita1 = glm::dot(AB, AC);					// �����Ƕȵ�cos
	float sita2 = glm::dot(BA, BC);
	if (sita1 >= 0 && sita2 >= 0)					// ��������Σ�˵����̾������߶���    
		return distance_line;
	else
		return min(glm::length(AC), glm::length(BC));
}

// �Ƿ񹹳�������
bool Geometry::isTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 CA = p1 - p3;
	glm::vec3 CB = p2 - p3;
	float area = glm::length(glm::cross(CA, CB));
	if (abs(area) < 1e-4)
		return false;
	return true;
}