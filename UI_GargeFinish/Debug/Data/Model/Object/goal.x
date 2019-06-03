xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 14;
 -0.00128;0.01600;-0.76002;,
 0.66296;0.01600;0.39048;,
 0.66296;-0.01600;0.39048;,
 -0.00128;-0.01600;-0.76002;,
 -0.66553;0.01600;0.39048;,
 -0.66553;-0.01600;0.39048;,
 -0.00128;0.01600;-0.76002;,
 -0.00128;-0.01600;-0.76002;,
 -0.00128;0.01600;0.00698;,
 -0.00128;0.01600;0.00698;,
 -0.00128;0.01600;0.00698;,
 -0.00128;-0.01600;0.00698;,
 -0.00128;-0.01600;0.00698;,
 -0.00128;-0.01600;0.00698;;
 
 9;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 3;8,1,0;,
 3;9,4,1;,
 3;10,6,4;,
 3;11,3,2;,
 3;12,2,5;,
 3;13,5,7;;
 
 MeshMaterialList {
  2;
  9;
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1;;
  Material {
   0.229020;0.250980;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.718431;0.715294;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  5;
  0.000000;1.000000;0.000000;,
  0.866025;0.000000;-0.500000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.866025;0.000000;-0.500000;;
  9;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;;
 }
 MeshTextureCoords {
  14;
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166667;0.000000;,
  0.500000;0.000000;,
  0.833333;0.000000;,
  0.166667;1.000000;,
  0.500000;1.000000;,
  0.833333;1.000000;;
 }
}
