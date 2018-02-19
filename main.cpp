#include <iostream>
#include <vtk-8.1/vtkGenericDataObjectReader.h>
#include <vtk-8.1/vtkStructuredGrid.h>
#include <vtk-8.1/vtkSmartPointer.h>
#include <vtk-8.1/vtkPolyData.h>
#include <vtk-8.1/vtkFieldData.h>
#include <vtk-8.1/vtkDoubleArray.h>
#include "helper.h"

swcFile outFileData;

int main(int argc, char* argv[]) {
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilename" << std::endl;
        return EXIT_FAILURE;
    }

    // Get the filename from the command line
    std::string inputFilename = argv[1];

    // Get all data from the file
    vtkSmartPointer<vtkGenericDataObjectReader> reader = vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    //vtkPolyData* output;
    vtkSmartPointer<vtkPolyData> output =  vtkSmartPointer<vtkPolyData>::New();
    output->ShallowCopy(reader->GetOutput());

//    vtkSmartPointer<vtkPolyData> output = vtkSmartPointer<vtkPolyData>::New();
//     All of the standard data types can be checked and obtained like this:
    if(reader->IsFilePolyData())
    {
        std::cout << "output is a polydata" << std::endl;
        std::cout << "output has " << output->GetNumberOfPoints() << " points." << std::endl;
        std::cout << "There are " << output->GetNumberOfLines() << " lines." << std::endl;
    }
//    vtkSmartPointer<vtkIntArray> intValue = vtkSmartPointer<vtkIntArray>::New();
//    intValue->SetNumberOfComponents(1);
//    intValue->SetName("MyIntValue");
//    intValue->InsertNextValue(5);
//
//    output->GetFieldData()->AddArray(intValue);

    vtkDoubleArray* field = vtkDoubleArray::SafeDownCast(output->GetFieldData()->GetArray("time_val"));

    std::cout << output -> GetFieldData() -> HasArray("time_val") << "\n";
    std::cout << output -> GetFieldData() -> GetNumberOfArrays() << "\n";

    output->GetLines()->InitTraversal();
    vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();

    while(output->GetLines()->GetNextCell(idList))
    {

        //std::cout << "Line has " << idList->GetNumberOfIds() << " points." << std::endl;

        for(vtkIdType pointId = 0; pointId < idList->GetNumberOfIds(); pointId++)
        {
            // preindex
            int id = idList -> GetId(pointId);
            if(pointId == 0){
                outFileData.preIndex.push_back(-1);
            }else{
                outFileData.preIndex.push_back(id);
            }

            // position
            double p[3];
            output->GetPoint(id, p);
            vec3f position;
            position.x = (float)p[0]; position.y = (float)p[1]; position.z = (float)p[2];
            outFileData.position.push_back(position);

            // index
            outFileData.index.push_back(outFileData.preIndex.size());

            //component
            outFileData.component.push_back(outFileData.preIndex.size());

            // radius
            outFileData.radius.push_back(0.1);
            // field
//            field -> GetValue(id);
//            std::cout << "debug" << std::endl;
//            std::cout << field -> GetValue(0) << " ";
        }

    }


    // DEBUG
    //    std::cout << outFileData.position.size() << "\n";
//    for(size_t i = 0; i < 500; ++i){
//        std::cout << outFileData.preIndex[i] << " ";
//    }
    // End of DEBUG

//    // Write all of the coordinates of the points in the vtkPolyData to the console.
//    for(vtkIdType i = 0; i < output->GetNumberOfPoints(); i++)
//    {
//        double p[3];
//        output->GetPoint(i,p);
//
//        // This is identical to:
//        // polydata->GetPoints()->GetPoint(i,p);
//        //std::cout << "Point " << i << " : (" << p[0] << " " << p[1] << " " << p[2] << ")" << std::endl;
//    }

    return EXIT_SUCCESS;
}