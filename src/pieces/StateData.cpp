#include <Urho3D/Urho3D.h>
#include "StateData.h"

StateData::StateData(Context* context):
    Object(context)
{
    stateNames_.Push("state_1");
    stateNames_.Push("state_2");
    stateNames_.Push("state_3");
    stateNames_.Push("state_4");
    stateNames_.Push("state_5");
    stateNames_.Push("state_6");
    stateNames_.Push("state_7");
    stateNames_.Push("state_8");
    stateNames_.Push("state_9");
    stateNames_.Push("state_10");
    stateNames_.Push("state_11");
    stateNames_.Push("state_12");
    stateNames_.Push("state_13");
    stateNames_.Push("state_14");
    stateNames_.Push("state_15");
    stateNames_.Push("state_16");
    stateNames_.Push("state_17");
    stateNames_.Push("state_18");
    stateNames_.Push("state_19");
    stateNames_.Push("state_20");
    stateNames_.Push("state_21");
    stateNames_.Push("state_22");
    stateNames_.Push("state_23");
    stateNames_.Push("state_24");
    stateNames_.Push("state_25");
    stateNames_.Push("state_26");
    stateNames_.Push("state_27");
    stateNames_.Push("state_28");
    stateNames_.Push("state_29");
    stateNames_.Push("state_30");
    stateNames_.Push("state_31");
    stateNames_.Push("state_32");
    stateNames_.Push("state_33");
    stateNames_.Push("state_34");
    stateNames_.Push("state_35");
    stateNames_.Push("state_36");
    stateNames_.Push("state_37");
    stateNames_.Push("state_38");
    stateNames_.Push("state_39");
    stateNames_.Push("state_40");
    stateNames_.Push("state_41");
    stateNames_.Push("state_42");
    stateNames_.Push("state_43");
    stateNames_.Push("state_44");
    stateNames_.Push("state_45");
    stateNames_.Push("state_46");
    stateNames_.Push("state_47");
    stateNames_.Push("state_48");
    stateNames_.Push("state_49");
    stateNames_.Push("state_50");

    stateMdls_.Push(String("state_1.001.mdl"));
    stateMdls_.Push(String("state_2.001.mdl"));
    stateMdls_.Push(String("state_3.001.mdl"));
    stateMdls_.Push(String("state_4.001.mdl"));
    stateMdls_.Push(String("state_5.001.mdl"));
    stateMdls_.Push(String("state_6.001.mdl"));
    stateMdls_.Push(String("state_7.001.mdl"));
    stateMdls_.Push(String("state_8.001.mdl"));
    stateMdls_.Push(String("state_9.001.mdl"));
    stateMdls_.Push(String("state_10.001.mdl"));
    stateMdls_.Push(String("state_11.001.mdl"));
    stateMdls_.Push(String("state_12.001.mdl"));
    stateMdls_.Push(String("state_13.001.mdl"));
    stateMdls_.Push(String("state_14.001.mdl"));
    stateMdls_.Push(String("state_15.001.mdl"));
    stateMdls_.Push(String("state_16.001.mdl"));
    stateMdls_.Push(String("state_17.001.mdl"));
    stateMdls_.Push(String("state_18.001.mdl"));
    stateMdls_.Push(String("state_19.001.mdl"));
    stateMdls_.Push(String("state_20.001.mdl"));
    stateMdls_.Push(String("state_21.001.mdl"));
    stateMdls_.Push(String("state_22.001.mdl"));
    stateMdls_.Push(String("state_23.001.mdl"));
    stateMdls_.Push(String("state_24.001.mdl"));
    stateMdls_.Push(String("state_25.001.mdl"));
    stateMdls_.Push(String("state_26.001.mdl"));
    stateMdls_.Push(String("state_27.001.mdl"));
    stateMdls_.Push(String("state_28.001.mdl"));
    stateMdls_.Push(String("state_29.001.mdl"));
    stateMdls_.Push(String("state_30.001.mdl"));
    stateMdls_.Push(String("state_31.001.mdl"));
    stateMdls_.Push(String("state_32.001.mdl"));
    stateMdls_.Push(String("state_33.001.mdl"));
    stateMdls_.Push(String("state_34.001.mdl"));
    stateMdls_.Push(String("state_35.001.mdl"));
    stateMdls_.Push(String("state_36.001.mdl"));
    stateMdls_.Push(String("state_37.001.mdl"));
    stateMdls_.Push(String("state_38.001.mdl"));
    stateMdls_.Push(String("state_39.001.mdl"));
    stateMdls_.Push(String("state_40.001.mdl"));
    stateMdls_.Push(String("state_41.001.mdl"));
    stateMdls_.Push(String("state_42.001.mdl"));
    stateMdls_.Push(String("state_43.001.mdl"));
    stateMdls_.Push(String("state_44.001.mdl"));
    stateMdls_.Push(String("state_45.001.mdl"));
    stateMdls_.Push(String("state_46.001.mdl"));
    stateMdls_.Push(String("state_47.001.mdl"));
    stateMdls_.Push(String("state_48.001.mdl"));
    stateMdls_.Push(String("state_49.001.mdl"));

    statePositions_.Push(Vector3(0.21888011694f,0.0156500004232f,2.09723997116f));
    statePositions_.Push(Vector3(2.54229521751f,-0.00904999952763f,1.75292992592f));
    statePositions_.Push(Vector3(2.41885995865f,-0.00999999977648f,1.90676009655f));
    statePositions_.Push(Vector3(0.673485100269f,0.0166000016034f,2.30860519409f));
    statePositions_.Push(Vector3(0.369050145149f,0.0175500009209f,1.11237001419f));
    statePositions_.Push(Vector3(0.516425132751f,0.0185000002384f,0.181779891253f));
    statePositions_.Push(Vector3(0.423860132694f,0.0185000002384f,0.481095075607f));
    statePositions_.Push(Vector3(0.577625155449f,0.0185000002384f,1.04367494583f));
    statePositions_.Push(Vector3(0.837990105152f,0.0185000002384f,1.52935504913f));
    statePositions_.Push(Vector3(0.935640096664f,0.0185000002384f,1.02947998047f));
    statePositions_.Push(Vector3(0.837135195732f,0.0185000002384f,0.446817427874f));
    statePositions_.Push(Vector3(1.17873501778f,0.0185000002384f,0.342575073242f));
    statePositions_.Push(Vector3(1.26694011688f,0.0185000002384f,0.743340015411f));
    statePositions_.Push(Vector3(1.27813506126f,0.0185000002384f,1.56136512756f));
    statePositions_.Push(Vector3(1.73834013939f,0.0175500009209f,1.89084005356f));
    statePositions_.Push(Vector3(1.36196017265f,0.0185000002384f,1.13154006004f));
    statePositions_.Push(Vector3(1.85952007771f,0.0185000002384f,1.51079499722f));
    statePositions_.Push(Vector3(1.88827514648f,0.000450000166893f,1.21628499031f));
    statePositions_.Push(Vector3(1.77227497101f,0.0175500009209f,0.656964957714f));
    statePositions_.Push(Vector3(1.77993512154f,-0.00144999939948f,0.365104973316f));
    statePositions_.Push(Vector3(2.22174501419f,-0.0052499989979f,0.468360185623f));
    statePositions_.Push(Vector3(2.69981503487f,-0.0052499989979f,0.614735066891f));
    statePositions_.Push(Vector3(2.4618601799f,-0.0052499989979f,0.627650141716f));
    statePositions_.Push(Vector3(2.53034496307f,-0.00810000021011f,1.0825150013f));
    statePositions_.Push(Vector3(2.75453519821f,-0.00714999902993f,1.07339000702f));
    statePositions_.Push(Vector3(2.99251008034f,-0.00714999902993f,0.980669975281f));
    statePositions_.Push(Vector3(3.74992036819f,-0.00810000021011f,0.702120065689f));
    statePositions_.Push(Vector3(3.66952991486f,-0.00619999971241f,0.732804954052f));
    statePositions_.Push(Vector3(3.72557497025f,-0.00619999971241f,0.641584992409f));
    statePositions_.Push(Vector3(3.53317499161f,-0.00904999952763f,1.00545012951f));
    statePositions_.Push(Vector3(3.5650601387f,-0.00619999971241f,0.886059999466f));
    statePositions_.Push(Vector3(3.40220499039f,-0.00429999921471f,1.02564501762f));
    statePositions_.Push(Vector3(3.82462024689f,-0.00239999918267f,0.349364906549f));
    statePositions_.Push(Vector3(3.70352506638f,-0.0052499989979f,0.491724967957f));
    statePositions_.Push(Vector3(3.60558986664f,-0.0052499989979f,0.511260032654f));
    statePositions_.Push(Vector3(3.44979000092f,-0.00429999921471f,0.630430102348f));
    statePositions_.Push(Vector3(3.3455851078f,-0.0052499989979f,0.875915110111f));
    statePositions_.Push(Vector3(2.3500752449f,-0.0052499989979f,1.56273007393f));
    statePositions_.Push(Vector3(3.1991353035f,-0.00144999939948f,1.08977997303f));
    statePositions_.Push(Vector3(3.26395010948f,-0.00144999939948f,1.17536497116f));
    statePositions_.Push(Vector3(2.79603528976f,-0.00714999902993f,1.73529994488f));
    statePositions_.Push(Vector3(2.81455516815f,-0.00144999939948f,1.42764496803f));
    statePositions_.Push(Vector3(3.25786995888f,-0.00144999939948f,1.38491988182f));
    statePositions_.Push(Vector3(3.21765995026f,-0.00619999971241f,1.58336496353f));
    statePositions_.Push(Vector3(3.04369020462f,-0.00429999921471f,1.68953490257f));
    statePositions_.Push(Vector3(3.07175517082f,-0.00999999977648f,2.11033010483f));
    statePositions_.Push(Vector3(1.79783010483f,0.0185000002384f,0.926185011864f));
    statePositions_.Push(Vector3(2.24017524719f,-0.00619999971241f,0.882490038872f));
    statePositions_.Push(Vector3(2.32092523575f,-0.0052499989979f,1.23307991028f));
    statePositions_.Push(Vector3(2.81634521484f,-0.00429999921471f,1.25435996056f));
}