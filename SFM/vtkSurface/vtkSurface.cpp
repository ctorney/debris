
#include "vtkSurface.h"
#include <iostream>
using namespace std;
void vtkSurface::draw() 
{
  vtkSmartPointer<vtkPolyData> input;
  if(-2 > 1)
    {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
   // reader->SetFileName(argv[1]);
   // reader->Update();
    input = reader->GetOutput();
    }
  else
    {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();
    input = sphereSource->GetOutput();
    }

       

  vtkSmartPointer<vtkPoints> points =  vtkSmartPointer<vtkPoints>::New();
  // Write all of the coordinates of the points in the vtkPolyData to the console.
  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
  {
      double p[3];
      input->GetPoint(i,p);

      // This is identical to:
      // polydata->GetPoints()->GetPoint(i,p);
  //    points->InsertNextPoint(p);
  }

    //    points->InsertNextPoint (1.0, 0.0, 0.0);
     //     points->InsertNextPoint (0.0, 1.0, 0.0);
  
  for (int i=0;i<100;i++)
  for (int j=0;j<100;j++)
  {
        double p[3];
        p[0] = 0.01*(float)i;
        p[1] = 0.01*(float)j;

        float d = powf(float(i)-50.0,2)+powf(float(j)-50.0,2);
        p[2] = 10.0*exp(-d);
      points->InsertNextPoint(p);
      std::cout << "Point " << i << " : (" << p[0] << " " << p[1] << " " << p[2] << ")" << std::endl;
  }

  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Construct the surface and create isosurface.	
  vtkSmartPointer<vtkSurfaceReconstructionFilter> surf = 
    vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  surf->SetInput(polydata);
#else
  surf->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkContourFilter> cf = 
    vtkSmartPointer<vtkContourFilter>::New();
  cf->SetInputConnection(surf->GetOutputPort());
  cf->SetValue(0, 0.0);

  // Sometimes the contouring algorithm can create a volume whose gradient
  // vector and ordering of polygon (using the right hand rule) are
  // inconsistent. vtkReverseSense cures this problem.
  vtkSmartPointer<vtkReverseSense> reverse = 
    vtkSmartPointer<vtkReverseSense>::New();
  reverse->SetInputConnection(cf->GetOutputPort());
  reverse->ReverseCellsOn();
  reverse->ReverseNormalsOn();

  cout<<"1hello"<<endl;
  vtkSmartPointer<vtkPolyDataMapper> map = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(reverse->GetOutputPort());
  map->ScalarVisibilityOff();

  cout<<"2hello"<<endl;
  vtkSmartPointer<vtkActor> surfaceActor = 
    vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(map);

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> ren = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  cout<<"3hello"<<endl;
  // Add the actors to the renderer, set the background and size
  ren->AddActor(surfaceActor);
  ren->SetBackground(.2, .3, .4);

  renWin->Render();
  iren->Start();

 // return EXIT_SUCCESS;

}

