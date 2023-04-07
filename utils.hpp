#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<unsigned char> convertImageToBlackAndWhite(string filename, int width, int height) {
    vector<unsigned char> imageBytes; // tableau de bytes pour stocker l'image en noir et blanc
    ifstream file(filename, ios::binary); // ouvre le fichier en mode binaire
    if (file.is_open()) {
        // saute l'en-tête de l'image
        file.seekg(54, ios::beg);

        // parcourt chaque pixel de l'image et calcule la moyenne des valeurs RGB
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // lit les trois composantes RGB du pixel
                unsigned char r, g, b;
                file.read((char*)&b, 1);
                file.read((char*)&g, 1);
                file.read((char*)&r, 1);

                // calcule la moyenne des valeurs RGB
                //unsigned char gray = (unsigned char)((int)r + (int)g + (int)b) / 3;
				unsigned char gray = (unsigned char)((int)r + (int)g + (int)b ) / 3;

                // stocke la valeur de l'intensité en noir et blanc dans le tableau de bytes
                imageBytes.push_back(gray);
            }
        }

        // ferme le fichier
        file.close();
    }

    return imageBytes;
}

vector<float> convertUnsignedCharToFloat(float* array, vector<unsigned char> vec){

	vector<float> vectorBytes ;
	unsigned int i = 0 ; 

	for(unsigned char c : vec){
		vectorBytes.push_back((float)c) ;
		array[i] = (float) c; 
		i++ ;
	}

	return vectorBytes ;

}

vector<unsigned char> convertFloatToUnsignedChar(float* vec, int size){

	vector<unsigned char> vectorBytes ;
	
	for(unsigned int i = 0 ; i < size ; i ++){
		vectorBytes.push_back((unsigned char)( (int)vec[i])) ;
	}

	return vectorBytes ;

}

void writeArrayToFile(float* array, int size, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file << (int) array[i] << "\n";
        }
        file.close();
        cout << "Array written to file " << filename << endl;
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}