/*
 * main.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: Tyler
 */

#include <iostream>
#include <fstream>

#include <vector>

#include <string.h>
#include <string>
#include <sstream>

#include <glm/glm.hpp>

int main() {
	std::cout << "Enter .obj file name to be converted\n\n";

	std::string inFileName;
	std::cin >> inFileName;
//	inFileName = "Cube.obj";

	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(inFileName.c_str(), std::ios::in);
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

			tempVertexArray.push_back(vertex);

		} else if (type == "vt") {
			std::istringstream stream(line.substr(2));
			glm::vec2 vertex;
			stream >> vertex.s;
			stream >> vertex.t;

			tempUVArray.push_back(vertex);

		} else if (type == "vn") {
			std::istringstream stream(line.substr(2));
			glm::vec3 normal;
			stream >> normal.x;
			stream >> normal.y;
			stream >> normal.z;

			tempNormalArray.push_back(normal);

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

			vertexIndexArray.push_back(v1 - 1);
			vertexIndexArray.push_back(v2 - 1);
			vertexIndexArray.push_back(v3 - 1);
			textureIndexArray.push_back(t1 - 1);
			textureIndexArray.push_back(t2 - 1);
			textureIndexArray.push_back(t3 - 1);
			normalIndexArray.push_back(n1 - 1);
			normalIndexArray.push_back(n2 - 1);
			normalIndexArray.push_back(n3 - 1);

		}
	}

	inFile.close();

	int numIndices = vertexIndexArray.size();

	for (int i = 0; i < numIndices; ++i) {
		unsigned int vertexIndex = vertexIndexArray[i];
		unsigned int textureIndex = textureIndexArray[i];
		unsigned int normalIndex = normalIndexArray[i];

		int similarIndex = -1;
		if (i == 0) {
			vertexArray.push_back(tempVertexArray[vertexIndex]);
			UVArray.push_back(tempUVArray[vertexIndex]);
			normalArray.push_back(tempNormalArray[vertexIndex]);

			indexArray.push_back(0);
			continue;
		}
		for (int j = 0; j < i; ++j) {
			bool vCheck = (vertexIndex == vertexIndexArray[j]);
			bool tCheck = (textureIndex == textureIndexArray[j]);
			bool nCheck = (normalIndex == normalIndexArray[j]);


			if (vCheck && tCheck && nCheck) { //Identical vertex already added
//				std::cout << i << ' ' << j << ' ' << vCheck << ' ' << tCheck << ' ' << nCheck << '\n';
//				std::cout << vertexIndex << '\n';
				similarIndex = indexArray[j];
				break;
			}
		}
		if (similarIndex == -1) {
			vertexArray.push_back(tempVertexArray[vertexIndex]);
			UVArray.push_back(tempUVArray[textureIndex]);
			normalArray.push_back(tempNormalArray[normalIndex]);
			indexArray.push_back(vertexArray.size() - 1);
		} else {
			indexArray.push_back(similarIndex);
		}
	}

//	for(unsigned int i = 0; i < vertexArray.size(); ++i){
//		std::cout << vertexArray[i].x << ' ' << vertexArray[i].y << ' ' << vertexArray[i].z << '\n';
//		std::cout << UVArray[i].x << ' ' << UVArray[i].y << '\n';
//		std::cout << normalArray[i].x << ' ' << normalArray[i].y << ' ' << normalArray[i].z << '\n';
//	}

//	for(unsigned int i = 0; i < indexArray.size(); ++i){
//		std::cout << indexArray[i] << '\n';
//	}

	std::string outFileName;
	std::cout << "Enter filename for output file\n";
	std::cin >> outFileName;

	while (outFileName == inFileName) {
		std::cerr << "Out file name can't be the same as In file name\n";
		std::cout << "Enter filename for output file\n";
		std::cin >> outFileName;

	}

	outFile.open(outFileName.c_str(), std::ios::out);

	if (!outFile.is_open()) {
		std::cerr << "Invalid output file name\n";
		return 1;
	}

	outFile << "gmdl\n";

	outFile << vertexArray.size() << ' ' << indexArray.size() << '\n';

	for (std::vector<glm::vec3>::iterator iterator = vertexArray.begin(); iterator != vertexArray.end(); ++iterator) {
		glm::vec3 vertex = *iterator;
		outFile << "v " << vertex.x << ' ' << vertex.y << ' ' << vertex.z << '\n';
	}
	for (std::vector<glm::vec2>::iterator iterator = UVArray.begin(); iterator != UVArray.end(); ++iterator) {
		glm::vec2 tex = *iterator;
		outFile << "t " << tex.x << ' ' << tex.y << '\n';
	}
	for (std::vector<glm::vec3>::iterator iterator = normalArray.begin(); iterator != normalArray.end(); ++iterator) {
		glm::vec3 normal = *iterator;
		outFile << "n " << normal.x << ' ' << normal.y << ' ' << normal.z << '\n';
	}
	for (std::vector<unsigned int>::iterator iterator = indexArray.begin(); iterator != indexArray.end(); iterator += 3) {
		unsigned int v1 = *iterator, v2 = *(iterator + 1), v3 = *(iterator + 2);
		outFile << "i " << v1 << ' ' << v2 << ' ' << v3 << '\n';
	}

	outFile.close();

	return 0;
}

