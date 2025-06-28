#pragma once

typedef struct _D3DMATRIX {
  union {
    struct {
      float _11, _12, _13, _14;
      float _21, _22, _23, _24;
      float _31, _32, _33, _34;
      float _41, _42, _43, _44;
    };
    float m[4][4];
  };
} D3DMATRIX;

typedef struct _D3DVECTOR {
  float x;
  float y;
  float z;
} D3DVECTOR;

typedef struct D3DXMATRIX {
public:
  D3DXMATRIX() {};
  D3DXMATRIX(const float *);
  D3DXMATRIX(const D3DMATRIX &);
  D3DXMATRIX(float m00, float m01, float m02, float m03, float m10, float m11,
             float m12, float m13, float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);

  // access grants
  float &operator()(unsigned iRow, unsigned iCol);
  float operator()(unsigned iRow, unsigned iCol) const;

  // casting operators
  operator float *();
  operator const float *() const;

  operator D3DMATRIX *();
  operator const D3DMATRIX *() const;

  operator D3DMATRIX &();
  operator const D3DMATRIX &() const;

  // assignment operators
  D3DXMATRIX &operator*=(const D3DXMATRIX &);
  D3DXMATRIX &operator+=(const D3DXMATRIX &);
  D3DXMATRIX &operator-=(const D3DXMATRIX &);
  D3DXMATRIX &operator*=(float);
  D3DXMATRIX &operator/=(float);

  // unary operators
  D3DXMATRIX operator+() const;
  D3DXMATRIX operator-() const;

  // binary operators
  D3DXMATRIX operator*(const D3DXMATRIX &) const;
  D3DXMATRIX operator+(const D3DXMATRIX &) const;
  D3DXMATRIX operator-(const D3DXMATRIX &) const;
  D3DXMATRIX operator*(float) const;
  D3DXMATRIX operator/(float) const;

  friend D3DXMATRIX operator*(float, const D3DXMATRIX &);

  bool operator==(const D3DXMATRIX &) const;
  bool operator!=(const D3DXMATRIX &) const;

  union {
    float m[4][4];
    struct {
      float m00, m01, m02, m03;
      float m10, m11, m12, m13;
      float m20, m21, m22, m23;
      float m30, m31, m32, m33;
    };
  };
} D3DXMATRIX, *LPD3DXMATRIX;

typedef struct D3DXVECTOR3 {
public:
  D3DXVECTOR3() {};
  D3DXVECTOR3(const float *);
  D3DXVECTOR3(const D3DVECTOR &);
  D3DXVECTOR3(float x, float y, float z);

  // casting
  operator float *();
  operator const float *() const;

  operator D3DVECTOR *();
  operator const D3DVECTOR *() const;

  operator D3DVECTOR &();
  operator const D3DVECTOR &() const;

  // assignment operators
  D3DXVECTOR3 &operator+=(const D3DXVECTOR3 &);
  D3DXVECTOR3 &operator-=(const D3DXVECTOR3 &);
  D3DXVECTOR3 &operator*=(float);
  D3DXVECTOR3 &operator/=(float);

  // unary operators
  D3DXVECTOR3 operator+() const;
  D3DXVECTOR3 operator-() const;

  // binary operators
  D3DXVECTOR3 operator+(const D3DXVECTOR3 &) const;
  D3DXVECTOR3 operator-(const D3DXVECTOR3 &) const;
  D3DXVECTOR3 operator*(float) const;
  D3DXVECTOR3 operator/(float) const;

  friend D3DXVECTOR3 operator*(float, const struct D3DXVECTOR3 &);

  bool operator==(const D3DXVECTOR3 &) const;
  bool operator!=(const D3DXVECTOR3 &) const;

public:
  float x, y, z;
} D3DXVECTOR3, *LPD3DXVECTOR3;

typedef struct D3DXVECTOR4 {
public:
  D3DXVECTOR4() {};
  D3DXVECTOR4(const float *);
  D3DXVECTOR4(float x, float y, float z, float w);

  // casting
  operator float *();
  operator const float *() const;

  // assignment operators
  D3DXVECTOR4 &operator+=(const D3DXVECTOR4 &);
  D3DXVECTOR4 &operator-=(const D3DXVECTOR4 &);
  D3DXVECTOR4 &operator*=(float);
  D3DXVECTOR4 &operator/=(float);

  // unary operators
  D3DXVECTOR4 operator+() const;
  D3DXVECTOR4 operator-() const;

  // binary operators
  D3DXVECTOR4 operator+(const D3DXVECTOR4 &) const;
  D3DXVECTOR4 operator-(const D3DXVECTOR4 &) const;
  D3DXVECTOR4 operator*(float) const;
  D3DXVECTOR4 operator/(float) const;

  friend D3DXVECTOR4 operator*(float, const D3DXVECTOR4 &);

  bool operator==(const D3DXVECTOR4 &) const;
  bool operator!=(const D3DXVECTOR4 &) const;

public:
  float x, y, z, w;
} D3DXVECTOR4, *LPD3DXVECTOR4;

float D3DXVec3Length(const D3DXVECTOR3 *pV);

float D3DXVec3LengthSq(const D3DXVECTOR3 *pV);

float D3DXVec3Dot(const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2);

// pOut->x = pV1->y * pV2->z - pV1->z * pV2->y;
// pOut->y = pV1->z * pV2->x - pV1->x * pV2->z;
// pOut->z = pV1->x * pV2->y - pV1->y * pV2->x;
D3DXVECTOR3 *D3DXVec3Cross(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                           const D3DXVECTOR3 *pV2);

D3DXVECTOR3 *D3DXVec3Add(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                         const D3DXVECTOR3 *pV2);

D3DXVECTOR3 *D3DXVec3Subtract(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                              const D3DXVECTOR3 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
D3DXVECTOR3 *D3DXVec3Minimize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                              const D3DXVECTOR3 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
D3DXVECTOR3 *D3DXVec3Maximize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                              const D3DXVECTOR3 *pV2);

D3DXVECTOR3 *D3DXVec3Scale(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV, float s);

// Linear interpolation. V1 + s(V2-V1)
D3DXVECTOR3 *D3DXVec3Lerp(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                          const D3DXVECTOR3 *pV2, float s);
D3DXVECTOR3 *D3DXVec3Normalize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
D3DXVECTOR3 *D3DXVec3Hermite(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                             const D3DXVECTOR3 *pT1, const D3DXVECTOR3 *pV2,
                             const D3DXVECTOR3 *pT2, float s);

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
D3DXVECTOR3 *D3DXVec3BaryCentric(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1,
                                 const D3DXVECTOR3 *pV2, const D3DXVECTOR3 *pV3,
                                 float f, float g);

// Transform (x, y, z, 1) by matrix.
D3DXVECTOR4 *D3DXVec3Transform(D3DXVECTOR4 *pOut, const D3DXVECTOR3 *pV,
                               const D3DXMATRIX *pM);

// Transform (x, y, z, 1) by matrix, project result back into w=1.
D3DXVECTOR3 *D3DXVec3TransformCoord(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV,
                                    const D3DXMATRIX *pM);

// Transform (x, y, z, 0) by matrix.
D3DXVECTOR3 *D3DXVec3TransformNormal(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV,
                                     const D3DXMATRIX *pM);
D3DXMATRIX *D3DXMatrixIdentity(D3DXMATRIX *pOut);

bool D3DXMatrixIsIdentity(const D3DXMATRIX *pM);

float D3DXMatrixfDeterminant(const D3DXMATRIX *pM);

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
D3DXMATRIX *D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1,
                               const D3DXMATRIX *pM2);

D3DXMATRIX *D3DXMatrixTranspose(D3DXMATRIX *pOut, const D3DXMATRIX *pM);

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
D3DXMATRIX *D3DXMatrixInverse(D3DXMATRIX *pOut, float *pfDeterminant,
                              const D3DXMATRIX *pM);

// Build a matrix which scales by (sx, sy, sz)
D3DXMATRIX *D3DXMatrixScaling(D3DXMATRIX *pOut, float sx, float sy, float sz);

// Build a matrix which translates by (x, y, z)
D3DXMATRIX *D3DXMatrixTranslation(D3DXMATRIX *pOut, float x, float y, float z);

// Build a matrix which rotates around the X axis
D3DXMATRIX *D3DXMatrixRotationX(D3DXMATRIX *pOut, float angle);

// Build a matrix which rotates around the Y axis
D3DXMATRIX *D3DXMatrixRotationY(D3DXMATRIX *pOut, float angle);

// Build a matrix which rotates around the Z axis
D3DXMATRIX *D3DXMatrixRotationZ(D3DXMATRIX *pOut, float angle);

// Build a matrix which rotates around an arbitrary axis
D3DXMATRIX *D3DXMatrixRotationAxis(D3DXMATRIX *pOut, const D3DXVECTOR3 *pV,
                                   float angle);

// Build a matrix from a quaternion
// D3DXMATRIX*  D3DXMatrixRotationQuaternion
//    ( D3DXMATRIX *pOut, const D3DXQUATERNION *pQ);

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
D3DXMATRIX *D3DXMatrixRotationYawPitchRoll(D3DXMATRIX *pOut, float yaw,
                                           float pitch, float roll);

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
// D3DXMATRIX*  D3DXMatrixTransformation
//    ( D3DXMATRIX *pOut, const D3DXVECTOR3 *pScalingCenter,
//      const D3DXQUATERNION *pScalingRotation, const D3DXVECTOR3 *pScaling,
//      const D3DXVECTOR3 *pRotationCenter, const D3DXQUATERNION *pRotation,
//      const D3DXVECTOR3 *pTranslation);

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
// D3DXMATRIX*  D3DXMatrixAffineTransformation
//    ( D3DXMATRIX *pOut, float Scaling, const D3DXVECTOR3 *pRotationCenter,
//      const D3DXQUATERNION *pRotation, const D3DXVECTOR3 *pTranslation);

// Build a lookat matrix. (right-handed)
D3DXMATRIX *D3DXMatrixLookAt(D3DXMATRIX *pOut, const D3DXVECTOR3 *pEye,
                             const D3DXVECTOR3 *pAt, const D3DXVECTOR3 *pUp);

// Build a lookat matrix. (left-handed)
D3DXMATRIX *D3DXMatrixLookAtLH(D3DXMATRIX *pOut, const D3DXVECTOR3 *pEye,
                               const D3DXVECTOR3 *pAt, const D3DXVECTOR3 *pUp);

// Build a perspective projection matrix. (right-handed)
D3DXMATRIX *D3DXMatrixPerspective(D3DXMATRIX *pOut, float w, float h, float zn,
                                  float zf);

// Build a perspective projection matrix. (left-handed)
D3DXMATRIX *D3DXMatrixPerspectiveLH(D3DXMATRIX *pOut, float w, float h,
                                    float zn, float zf);

// Build a perspective projection matrix. (right-handed)
D3DXMATRIX *D3DXMatrixPerspectiveFov(D3DXMATRIX *pOut, float fovy, float aspect,
                                     float zn, float zf);

// Build a perspective projection matrix. (left-handed)
D3DXMATRIX *D3DXMatrixPerspectiveFovLH(D3DXMATRIX *pOut, float fovy,
                                       float aspect, float zn, float zf);

// Build a perspective projection matrix. (right-handed)
D3DXMATRIX *D3DXMatrixPerspectiveOffCenter(D3DXMATRIX *pOut, float l, float r,
                                           float b, float t, float zn,
                                           float zf);

// Build a perspective projection matrix. (left-handed)
D3DXMATRIX *D3DXMatrixPerspectiveOffCenterLH(D3DXMATRIX *pOut, float l, float r,
                                             float b, float t, float zn,
                                             float zf);

// Build an ortho projection matrix. (right-handed)
D3DXMATRIX *D3DXMatrixOrtho(D3DXMATRIX *pOut, float w, float h, float zn,
                            float zf);

// Build an ortho projection matrix. (left-handed)
D3DXMATRIX *D3DXMatrixOrthoLH(D3DXMATRIX *pOut, float w, float h, float zn,
                              float zf);

// Build an ortho projection matrix. (right-handed)
D3DXMATRIX *D3DXMatrixOrthoOffCenter(D3DXMATRIX *pOut, float l, float r,
                                     float b, float t, float zn, float zf);

// Build an ortho projection matrix. (left-handed)
D3DXMATRIX *D3DXMatrixOrthoOffCenterLH(D3DXMATRIX *pOut, float l, float r,
                                       float b, float t, float zn, float zf);

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
// D3DXMATRIX*  D3DXMatrixShadow
//    ( D3DXMATRIX *pOut, const D3DXVECTOR4 *pLight,
//      const D3DXPLANE *pPlane );

// Build a matrix which reflects the coordinate system about a plane
// D3DXMATRIX*  D3DXMatrixReflect
//    ( D3DXMATRIX *pOut, const D3DXPLANE *pPlane );

using Vector = D3DXVECTOR3;
using Matrix = D3DXMATRIX;

const Vector &ExtractRow(const Matrix &mtx, int rowIndex);
void InsertRow(Matrix &mtx, int rowIndex, const Vector &row);
Vector operator*(const Vector &v0, const Vector &v1);
