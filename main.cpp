/*
 * main.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: Tyler
 */

#include <iostream>
#include <fstream>

#include <vector>

#include <string>
#include <sstream>

#include <glm/glm.hpp>

int main() {

	std::cout << "Enter .obj file name to be converted\n\n";

	std::string filePath;
	std::cin >> filePath;

	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(filePath.c_str(), std::ios::in);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file\n";
		return 1;
	}

	std::vector<glm::vec3> vertexArray, tempVertexArray;
	std::vector<glm::vec2> UVArray, tempUVArray;
	std::vector<glm::vec3> normalArray, tempNormalArray;
	std::vector<unsigned int> indexArray, vertexIndexArray, textureIndexArray, normalIndexArray;

	std::string line;
	while (getline(inFile, line)) {
		std::string type = line.substr(0, 2);
		if (type == "v ") {
			std::istringstream stream(line.substr(2));
			glm::vec3 vertex;
			stream >> vertex.x;
			stream >> vertex.y;
			stream >> vertex.z;

		} else if (type == "vt") {
			std::istringstream stream(line.substr(2));
			glm::vec2 vertex;
			stream >> vertex.s;
			stream >> vertex.t;

		} else if (type == "vn") {
			std::istringstream stream(line.substr(2));
			glm::vec3 normal;
			stream >> normal.x;
			stream >> normal.y;
			stream >> normal.z;

		} else if (type == "f ") {
			std::istringstream stream(line.substr(2));
			unsigned int v1, t1, n1, v2, t2, n2, v3, t3, n3;
			stream >> v1;
			stream.ignore(1);
			stream >> t1;
			stream.ignore(1);
			stream >> n1;
			stream.ignore(1);
			stream >> v2;
			stream.ignore(1);
			stream >> t2;
			stream.ignore(1);
			stream >> n2;
			stream.ignore(1);
			stream >> v3;
			stream.ignore(1);
			stream >> t3;
			stream.ignore(1);
			stream >> n3;

		}
	}

}

