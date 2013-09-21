#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <dfsd.h>
#include <mfhdf.h>
#include <hdf.h>
#include <gdal.h>

#include <sys/types.h>
//#include "libpq-fe.h"

typedef struct
{
    float32 lat;
    float32 lon;

    // surface reclectance for bands
    int16 sr_b01; //  Surface_reflectance_for_band_1
    int16 sr_b02; //  Surface_reflectance_for_band_2
    int16 sr_b03; //  Surface_reflectance_for_band_3
    // int16 sr_b04; //  Surface_reflectance_for_band_4
    // int16 sr_b05; //  Surface_reflectance_for_band_5
    int16 sr_b06; //  Surface_reflectance_for_band_6
    // int16 sr_b07; //  Surface_reflectance_for_band_7

    // // quality control
    // uint32 sr_qc_500m;        //  Surface_reflectance_500m_quality_control_flags
    // int16 sr_szen;            //  Solar_zenith
    // int16 sr_vzen;            //  View_zenith
    // int16 sr_raz;             //  Relative_azimuth
    // uint16 sr_state_500m;     //  Surface_reflectance_500m_state_flags
    // uint16 sr_day_of_year;    //  Surface_reflectance_day_of_year


} CombiData;

GByte getHDFMODPixelValueT(char *fMODISName, char *bName, int bNum, VOIDP outRaster);
void 	findDimension(char *nameInputFile, int **arrayDimension, char *nameBand);
void 	getFactor(char * inputFileName, char * band, char *attribute, float **valueToSearch);



int main (int argc, char **argv){
    char *fMOD09A1Name = NULL;
	int *dimDataset, dx, dy, k, j, pos;

    int16 *sr_b01 = NULL;
    int16 *sr_b02 = NULL;
    int16 *sr_b03 = NULL;
    // int16 *sr_b04 = NULL;
    // int16 *sr_b05 = NULL;
    int16 *sr_b06 = NULL;
    // int16 *sr_b07 = NULL;

    // uint32 *sr_qc_500m;
    // int16 *sr_szen;
    // int16 *sr_vzen;
    // int16 *sr_raz;
    // uint16 *sr_state_500m;
    // uint16 *sr_day_of_year;

    GByte resHdf;
    CombiData data;

    // file name
    fMOD09A1Name = "MOD09A1.A2010001.h27v06.005.2010011070514.hdf";

    // band name
    findDimension(fMOD09A1Name, &dimDataset, "sur_refl_b01");
	dy =	(int) dimDataset[0];
	dx = 	(int) dimDataset[1];

	printf("%d - %d: \n", dx, dy);

    // MOD09A1
	sr_b01  = (int16 *)malloc(sizeof(int16) * dx * dy);
	sr_b02 	= (int16 *)malloc(sizeof(int16) * dx * dy);
	sr_b03 	= (int16 *)malloc(sizeof(int16) * dx * dy);
	// sr_b04 	= (int16 *)malloc(sizeof(int16) * dx * dy);
	// sr_b05 	= (int16 *)malloc(sizeof(int16) * dx * dy);
	sr_b06 	= (int16 *)malloc(sizeof(int16) * dx * dy);
	// sr_b07 	= (int16 *)malloc(sizeof(int16) * dx * dy);

    if (sr_b01 == NULL || sr_b02 == NULL || sr_b03 == NULL || sr_b06 == NULL){
        printf ("Malloc Error");
        return (1);
    }
 //    if (sr_b01 == NULL || sr_b02 == NULL || sr_b03 == NULL || sr_b04 == NULL ||
 //        sr_b05 == NULL || sr_b06 == NULL || sr_b07 == NULL){
 //        printf ("Malloc Error");
 //        return (1);
	// }

 //    sr_qc_500m  = (uint32 *)malloc(sizeof(uint32) * dx * dy);
 //    sr_szen     = (int16 *)malloc(sizeof(int16) * dx * dy);
 //    sr_vzen     = (int16 *)malloc(sizeof(int16) * dx * dy);
 //    sr_raz      = (int16 *)malloc(sizeof(int16) * dx * dy);
 //    sr_state_500m   = (uint16 *)malloc(sizeof(uint16) * dx * dy);
 //    sr_day_of_year  = (uint16 *)malloc(sizeof(uint16) * dx * dy);

 //    if (sr_qc_500m == NULL || sr_szen == NULL || sr_vzen == NULL ||
 //        sr_raz == NULL || sr_state_500m == NULL || sr_day_of_year == NULL){
 //        printf ("Malloc Error");
 //        return (1);
	// }

	// Get surface relfectance at 7 bands
	resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b01", 0, sr_b01);
	resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b02", 0, sr_b02);
	resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b03", 0, sr_b03);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b04", 0, sr_b04);
	//resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b05", 0, sr_b05);
	resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b06", 0, sr_b06);
	//resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_b07", 0, sr_b07);

	// Get quality Control
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_qc_500m", 0, sr_qc_500m);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_szen", 0, sr_szen);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_vzen", 0, sr_vzen);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_raz", 0, sr_raz);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_state_500m", 0, sr_state_500m);
	// resHdf= getHDFMODPixelValueT (fMOD09A1Name, "sur_refl_day_of_year", 0, sr_day_of_year);

    FILE *outNVDI = fopen("nvdiResult", "w");
    FILE *outLSWI = fopen("lswiResult", "w");
    FILE *outEVI = fopen("eviResult", "w");

    // Extract combination data
    for (k=0; k<dx; k++)
    {
        for (j=0; j<dy; j++)
        {
            pos = k*dx + j;
            data.sr_b01 = (int16)((long int)sr_b01[pos]);
            data.sr_b02 = (int16)((long int)sr_b02[pos]);
            data.sr_b03 = (int16)((long int)sr_b03[pos]);
            // data.sr_b04 = (int16)((long int)sr_b04[pos]);
            // data.sr_b05 = (int16)((long int)sr_b05[pos]);
            data.sr_b06 = (int16)((long int)sr_b06[pos]);
            // data.sr_b07 = (int16)((long int)sr_b07[pos]);

            // data.sr_qc_500m = (uint32)((long int)sr_qc_500m[pos]);
            // data.sr_szen = (int16)((long int)sr_szen[pos]);
            // data.sr_vzen = (int16)((long int)sr_vzen[pos]);
            // data.sr_raz = (int16)((long int)sr_raz[pos]);
            // data.sr_state_500m = (uint16)((long int)sr_state_500m[pos]);
            // data.sr_day_of_year = (uint16)((long int)sr_day_of_year[pos]);

            float nvdi = (float)(data.sr_b02 - data.sr_b01)/(data.sr_b02 + data.sr_b01);
            float lswi = (float)(data.sr_b02 - data.sr_b06)/(data.sr_b02 + data.sr_b06);
            float evi = 2.5*((data.sr_b02 - data.sr_b01)/(data.sr_b02 + 6*data.sr_b01 - 7.5*data.sr_b03 + 1));

            fprintf(outNVDI, "%f ", nvdi);
            fprintf(outLSWI, "%f ", lswi);
            fprintf(outEVI, "%f ", evi);
    	    /*printf ("Position %4d %4d\t=\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n"
                 ,k, j, data.sr_b01, data.sr_b02, data.sr_b03, data.sr_b04, data.sr_b05, data.sr_b06, data.sr_b07,
                 data.sr_qc_500m, data.sr_szen, data.sr_vzen, data.sr_raz, data.sr_state_500m, data.sr_day_of_year);*/
        }
        fprintf(outNVDI, "\n");
        fprintf(outLSWI, "\n");
        fprintf(outEVI, "\n");
    }

	free (sr_b01);
	free (sr_b02);
	free (sr_b03);
	// free (sr_b04);
	// free (sr_b05);
	free (sr_b06);
	// free (sr_b07);

	// free (sr_qc_500m);
	// free (sr_szen);
	// free (sr_vzen);
	// free (sr_raz);
	// free (sr_state_500m);
	// free (sr_day_of_year);

    fclose(outNVDI);
    fclose(outLSWI);
    fclose(outEVI);

    return 0;
}




// ******************************************************
// Read HDF file

GByte getHDFMODPixelValueT(char *fMODISName, char *bName, int bNum, VOIDP outRaster){

	int32 SDidentifier; // Scientific Data identifier

	if (( SDidentifier = SDstart(fMODISName, DFACC_READ)) == FAIL ){
        printf("ERROR: Unable to open inputfile '%s'\n", fMODISName);
        exit(1);}

	int32 nDatasets;
	int32 nGlobalAttrs;
	SDfileinfo(SDidentifier, &nDatasets, &nGlobalAttrs);

	int out_index= -1;
	int i;

	int32 DataSetId; // Data Set identifier
	char DataSetName[255]; // Name of the data set
	int32 DataSetDimensionNumber; // Number of dimensions in the data set; the maximum value is MAX_VAR_DIMS (or 32)
	int32 DataSetDimensionSizes[3]; // Array containing the size of each dimension in the data set; Y e X
	int32 DataSetDataType; // Data type for the data stored in the data set
	int32 DataSetNumAttrs; // Number of attributes for the data set

	for(i=0; i < nDatasets; i++){
        if ((DataSetId = SDselect(SDidentifier, i)) == FAIL) {
            printf ("ERROR: Unables select dataset #%d\n", i);
            exit(2);}

        SDgetinfo(DataSetId, DataSetName, &DataSetDimensionNumber, DataSetDimensionSizes,
                  &DataSetDataType, &DataSetNumAttrs);

        if( !strcmp(DataSetName, bName)){
            out_index = DataSetId;
            printf ("getHDFMODPixelValueT()--> DS: '%s'\n", DataSetName);
            i= nDatasets;}
        if (SDendaccess(DataSetId) == FAIL) {
            printf ("ERROR: Unable to close SDS\n");
            exit(3);}
	}	// end for

	if(out_index== -1){
        printf ("getHDFMODPixelValueT()--> ERROR: No Data Set named '%s'\n", bName);
        exit(4);}

	int32 edges[DataSetDimensionNumber]; // Array specifying the number of values to be read along each dimension
	int32 start[DataSetDimensionNumber]; // Array specifying from where start read values

	if (DataSetDimensionNumber == 3){
		start[0] = bNum;
		start[1] = 0;
		start[2] = 0;

		edges[0] = 1;
		edges[1] = DataSetDimensionSizes[1];	// 2030 in MOD021km
		edges[2] = DataSetDimensionSizes[2];	// 1354 in MOD021km
	}
	else {
		start[0] = 0;
		start[1] = 0;

		edges[0] = DataSetDimensionSizes[0];	// 2030 in MOD021km
		edges[1] = DataSetDimensionSizes[1];	// 1354 in MOD021km

	}

	intn SDcode;
	if((SDcode = SDreaddata(out_index, start, NULL, edges, (VOIDP)outRaster)) == FAIL){
        printf ("getHDFMODPixelValueT()--> ERROR: Loading error \n");
        exit(7);}

	return 0;
}

// ******************************************************
// Read Dataset Dimension

void findDimension(char *nameInputFile, int **arrayDimension, char *nameBand){

	int32 SDidentifier; // Scientific Data identifier
	if(( SDidentifier = SDstart(nameInputFile, DFACC_READ)) == FAIL ){
        printf("ERROR: Unable to open inputfile '%s'\n", nameInputFile);
        exit(1);}

	int32 nDatasets;
	int32 nGlobalAttrs;
	SDfileinfo(SDidentifier, &nDatasets, &nGlobalAttrs); // get information about the Input Dataset

	int32 DataSetId; // SubDataset identifier
	char DataSetName[255]; // Name of the data set
	int32 DataSetDimensionNumber; // Number of dimensions in the data set; the maximum value is MAX_VAR_DIMS (or 32)
	int32 DataSetDimensionSizes[3]; // Array containing the size of each dimension in the data set; Y e X
	int32 DataSetDataType; // Data type for the data stored in the data set
	int32 DataSetNumAttrs; // Number of attributes for the data set

	int i;
	int n;
	for(i=0; i< nDatasets; i++){ // access to all SubDatasets

		if((DataSetId = SDselect(SDidentifier, i)) == FAIL){ // if it's not possible open 'i' SubDataset
			printf ("ERROR: Unables select SubDataset #%d\n", i);
			exit(2);
		}
		SDgetinfo(DataSetId, DataSetName, &DataSetDimensionNumber, DataSetDimensionSizes, &DataSetDataType, &DataSetNumAttrs);
		if(0 == strcmp(DataSetName, nameBand)){
			*arrayDimension= (int *)malloc(sizeof(int)*DataSetDimensionNumber);
			for(n=0; n<DataSetDimensionNumber; n++)
				(*arrayDimension)[n]= DataSetDimensionSizes[n];
		}
	} // end Subdatasets for cycle

}

// ******************************************************
// Read Factor (scale and offset)


void getFactor(char * inputFileName, char * band, char *attribute, float **valueToSearch){

	int32 SDidentifier; // Scientific Data identifier

	if (( SDidentifier = SDstart(inputFileName, DFACC_READ)) == FAIL ){
        printf("ERROR: Unable to open inputfile '%s'\n", inputFileName);
        exit(1);}
	int32 nDatasets;
	int32 nGlobalAttrs;
	SDfileinfo(SDidentifier, &nDatasets, &nGlobalAttrs);

	int32 subDataSetId; // Data Set identifier
	char DataSetName[255]; // Name of the data set
	int32 DataSetDimensionNumber; // Number of dimensions in the data set; the maximum value is MAX_VAR_DIMS (or 32)
	int32 DataSetDimensionSizes[3]; // Array containing the size of each dimension in the data set; Y e X
	int32 DataSetDataType; // Data type for the data stored in the data set
	int32 DataSetNumAttrs; // Number of attributes for the data set

	int32 out_index= -1;
	int i;
	for(i=0; i < nDatasets; i++){
        if ((subDataSetId = SDselect(SDidentifier, i)) == FAIL) {
            printf ("ERROR: Unables select dataset #%d\n", i);
            exit(2);}

        SDgetinfo(subDataSetId, DataSetName, &DataSetDimensionNumber, DataSetDimensionSizes,
                  &DataSetDataType, &DataSetNumAttrs);

        if( !strcmp(DataSetName, band)){
            out_index = subDataSetId;
            printf ("getReflectanceFactor()--> DS: '%s'\n", DataSetName);
            i= nDatasets;}
        if (SDendaccess(subDataSetId) == FAIL) { // to end a 'SDcreate' or a 'SDselect'
            printf ("ERROR: Unable to close SDS\n");
            exit(3);}
	} // end for

	if(out_index== -1){
        printf("getReflectanceFactor()--> ERROR: No Data Set named '%s'\n", band);
        exit(4);}

    int32 attr_index, num_type, count;
    char attr_name[64];
    int k;

	attr_index = SDfindattr(out_index, attribute);
    if (attr_index == FAIL){
        printf ("ERROR: SDfindattr failed %s\n", attribute);
        exit(5);}

	printf("getReflectanceFactor()--> Found '%s' attribute\n", attribute);

	// Get information about the file attribute
    if (SDattrinfo(out_index, attr_index, attr_name, &num_type, &count) == FAIL){
        printf ("ERROR: SDattrinfo failed\n");
        exit(6);
	}

    *valueToSearch= (float *)malloc(sizeof(float) * count);
    if(valueToSearch== NULL){
        printf("ERROR: can not malloc()\n");
        exit(7);
    }

	float buffer[count];
	// --------------------------------

    // Read the attribute data
    if(SDreadattr(out_index, attr_index, buffer) == FAIL){
        printf ("ERROR: SDreadattr failed\n");
        exit(8);}
	for(k=0; k<count; k++)
        (*valueToSearch)[k]= (buffer[k]);

    // Terminate access to the array
    int status = SDendaccess(out_index);
    if (status == FAIL){
        printf ("ERROR: SDendaccess failed\n");
        exit(9);}

    // Terminate access to the SD interface and close the file
    status = SDend(SDidentifier); // to end a 'SDstart'
    if (status == FAIL){
        printf ("ERROR: SDend failed\n");
        exit(10);}
}
// ******************************************************
