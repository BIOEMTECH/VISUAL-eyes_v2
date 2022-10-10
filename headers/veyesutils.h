#ifndef VEYESUTILS_H
#define VEYESUTILS_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <TH1F.h>
#include <TSpectrum.h>

namespace veyesUtils {
        template<typename T>
        static T** allocate_2D_array(int size_x, int size_y){
            T ** array = new T*[size_x];
            for (int i=0; i<size_x;i++){
                array[i] = new T[size_y] ;
            }
            return array;
        }
        template<typename T>
        static T*** allocate_3D_array(int size_x,int size_y, int size_z){
                T*** array = new T**[ size_x ];
                for (int i = 0; i < size_x; i++){
                    array[i] = new T*[size_y];

                    for (int j = 0; j < size_y; j++)
                        array[ i ][ j ] = new T[ size_z];
                }
                return array;
        }
        template<typename T>
        static void clear_1D_array(T*&array, int size_x){
            for (int i = 0; i < size_x; i++)
                array[i] = 0;
        }
        template<typename T>
        static void clear_2D_array(T**& array, int size_x, int size_y){
            for (int i = 0; i < size_x; i++)
                for (int j = 0; j < size_y; j++)
                    array[i][j] = 0;
        }
        template<typename T>
        static void clear_3D_array(T***& array, int size_x, int size_y,int size_z){
            for (int i = 0; i < size_x; i++)
                for (int j = 0; j < size_y; j++)
                    for (int k = 0; k < size_z; k++)
                            array[i][j][k] = 0;
        }
        template<typename T>
        static void delete_2D_array(T**& array, int size_x){
            if(array){
                for (int i = 0; i < size_x; i++)
                    delete [] array[i];

                delete [] array;
            }
        }
        template<typename T>
        static void delete_3D_array(T***& array, int size_x, int size_y){
            if (array){
                for (int i = 0; i < size_x; i++){
                    for (int j = 0; j < size_y; j++)
                          delete[] array[i][j];

                     delete [] array[i];
                }
            }
        }
        template<typename T>
        static T sum_2D_array(T** array,int size_x,int size_y){
                T sum=0;
                for (int i = 0; i < size_x; i++ )
                    for (int j = 0; j < size_y; j++ )
                        sum +=  array[i][j] ;

                return sum;
        }
        template<typename T>
        static cv::Mat array2D_to_cvmat(T** array, int size_x, int size_y, float correction){
                cv::Mat image(size_x, size_y, CV_32F);
                float input_image[size_x*size_y];
                for (int i=0; i<size_x; i++){
                    for(int j=0;j<size_y;j++)
                        input_image[i*size_y+j] = array[i][j]*correction;
                }

                std::memcpy(image.data, input_image, size_x * size_y * sizeof(input_image[0]));
                return image;

        }
        static cv::Mat image_conversion(cv::Mat input_image, double scale_factor_x, double scale_factor_y,int size_x, int size_y){
                double min=0.0, max=0.0;
                int outputRows = int(scale_factor_x * size_x);
                int outputCols = int(scale_factor_y * size_y);
                cv::Mat converted_image(outputRows,outputCols, CV_32F);

                cv::resize(input_image,converted_image,converted_image.size(),scale_factor_x,scale_factor_x,cv::INTER_CUBIC);
                cv::minMaxLoc(input_image, &min, &max);
                cv::threshold(converted_image,converted_image,0, max, cv::THRESH_TOZERO);

                return converted_image;
        }
        static void write_txt_image(std::string filepath,cv::Mat img, int size_x, int size_z)
        {
            FILE* output_file = fopen(filepath.c_str(), "w" );

            for ( int i = 0; i< size_x; i++){
                for ( int j = 0; j< size_z; j++)
                    fprintf( output_file, "%f ", img.at<float>(i,j)  );

                fprintf(output_file, "\n");
            }
            fclose( output_file );
        }

        static int read_castor_header(QString filepath){
            QFile castor_header_file(filepath);
            int no_events = 0;

            if (castor_header_file.open(QIODevice::ReadOnly)){
                QTextStream in( &castor_header_file );
                while ( !in.atEnd() )
                {
                    QString line  = in.readLine();
                    if ( line.isEmpty() ) continue;

                    QStringList tokens = line.split(":");

                    if ( tokens[ 0 ] == "Number of events")
                        no_events = tokens[ 1].trimmed().toInt();
                }

            }
            else {
                std::cout << "Could not open " + filepath.toStdString() << std::endl;
                no_events=0;
            }
            castor_header_file.close();
            if ( no_events == 0)
                std::cout << "WARNING: Something is wrong with the number of events. Check header.Cdh file." << std::endl;

            return no_events;
        }

        static void read_img(std::string filepath, float***& array,int size_x,int size_y, int size_z){
            FILE* img = fopen( filepath.c_str(), "rb" );
            if ( img == nullptr )
                std::cout << "WARNING: Could not open image in " + filepath << std::endl;

            for ( int i = 0; i< size_z; i++)
                for ( int j = 0; j< size_y; j++)
                    for (int k = 0; k < size_x; k++)
                        fread( &array[k][j][i], sizeof(float), 1, img);
            fclose( img );

        }

        static void img_smoothing(float***& array,float*** flood,float mean[],float mean_flood[],int size_x,int size_y, int size_z){
            for ( int i = 1; i< size_z-1; i++){
                for ( int j = 0; j< size_y; j++){
                    for (int k = 1; k < size_x-1; k++){
                        if (((i < 5) || (i > size_z-5)) || ((k < 5) || (k > size_x-5))){
                            if (array[k][j][i] > 50*mean[j]){
                                array[k][j][i] = (array[k-1][j][i] + array[k-1][j][i+1]
                                                 +array[k-1][j][i-1 ] + array[k][j][i-1]
                                                 +array[k][j][i+1] + array[k+1][j][i]
                                                 +array[k+1][j][i+1] + array[k+1][j][i-1])/8;
                            }
                            if (array[k][j][i] > 50*mean_flood[j]){
                                array[k][j][i] = (flood[k-1][j][i] + flood[k-1][j][i+1]
                                                       + flood[k-1][j][i-1] + flood[k][j][i-1]
                                                       + flood[k][j][i+1] + flood[k+1][j][i]
                                                       + flood[k+1][j][i+1] + flood[k+1][j][i-1])/8;
                            }
                        }
                    }
                }
            }

        }

        static void to_zero(float**& array,int size_x,int size_z){
            for ( int i = 1; i< size_z-1; i++){
                    for (int k = 1; k < size_x-1; k++){
                            if (((array[k][i] + array[k-1][i] + array[k-1][i+1] +
                            array[k-1][i-1] + array[k][i-1] + array[k][i+1] +
                            array[k+1][i] + array[k+1][i+1] + array[k+1][i-1])/2) <= array[k][i])
                            {
                                array[k][i] = 0;
                            }
                    }
            }
        }


        static float mf_decayCorrection(bool useDecay, bool doDecay,double activity,QString activity_unit,double lambda,double dt1,double frame_time,double elapsed_inject_time, double preExp, double nuclide_limit)
        {

            if ( activity < 1.e-10 )
                return 1.0;

            if (useDecay){
                if ( doDecay ){
                    double A = 0.0;
                    double t = elapsed_inject_time;

                    if ( activity_unit == "MBq")
                        A = 27.027*preExp*exp(-lambda*t);
                    else
                        A = preExp*exp(-lambda*t);

                    if ( A > nuclide_limit ) return 1.0;

                    if ( t > 1e-13 )
                        return A;
                }
                else
                    return 1.0;
            }
            else {
                if ( doDecay ){
                    if ( dt1 > 1e-13 )
                        return exp(lambda*dt1)*lambda*frame_time /(1. - exp(-lambda*frame_time));
                    else
                        return 1.0;
                }
            }
            return 1.0;
        }


        static float searchPhotopeak(TH1F* histo) {

            TSpectrum* s2 = new TSpectrum(1, 1);
            int nfounds = s2->Search(histo, 6, "nobackground", 0.05);
            double* xPositionsPeaks = s2->GetPositionX();
            double* yPositionsPeaks = s2->GetPositionY();
            float ymaxPeak1 = 0;
            float ymaxPeak2 = 0;
            float ymaxPeak3 = 0;
            float xmaxPeak1 = 0;
            float xmaxPeak2 = 0;
            float xmaxPeak3 = 0;


            for (int i = 0; i < nfounds; i++) {
                if (yPositionsPeaks[i] > ymaxPeak1) {
                    xmaxPeak3 = xmaxPeak2;
                    ymaxPeak3 = ymaxPeak2;
                    xmaxPeak2 = xmaxPeak1;
                    ymaxPeak2 = ymaxPeak1;
                    xmaxPeak1 = xPositionsPeaks[i];
                    ymaxPeak1 = yPositionsPeaks[i];
                    yPositionsPeaks[i] = -1;
                }

                if (yPositionsPeaks[i] > ymaxPeak2 && yPositionsPeaks[i] < ymaxPeak1) {
                    xmaxPeak3 = xmaxPeak2;
                    ymaxPeak3 = ymaxPeak2;
                    xmaxPeak2 = xPositionsPeaks[i];
                    ymaxPeak2 = yPositionsPeaks[i];
                }
                else if (yPositionsPeaks[i] > ymaxPeak3 && yPositionsPeaks[i] < ymaxPeak2) {
                    xmaxPeak3 = xPositionsPeaks[i];
                    ymaxPeak3 = yPositionsPeaks[i];
                }
            }

            if (xmaxPeak1 > xmaxPeak2) {
                if (xmaxPeak3>xmaxPeak1){
                    return xmaxPeak3;
                }
                else {
                    return xmaxPeak1;
                }
            }
            else {
                if (xmaxPeak3>xmaxPeak2){
                    return xmaxPeak3;
                }
                else {
                    return xmaxPeak2;
                }
            }
        }

        static long long returnTheNumberOfLines(FILE *file)
        {
            long long numberOfLines = 0;
            char k;

            while ((k=getc(file)) != EOF)
                if (k == '\n')
                    numberOfLines++;

            rewind(file);

            return numberOfLines;
        }



}

#endif // VEYESUTILS_H
