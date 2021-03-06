#ifndef OCTOON_MODTYPES_H_
#define OCTOON_MODTYPES_H_

#include <memory>
#include <vector>
#include <functional>

#include <octoon/math/math.h>
#include <octoon/runtime/platform.h>
#include <octoon/io/iostream.h>

#define MATKEY_NAME               "?mat.name",0,0
#define MATKEY_TWOSIDED           "$mat.twosided",0,0
#define MATKEY_SHADING_MODEL      "$mat.shadingm",0,0
#define MATKEY_ENABLE_WIREFRAME   "$mat.wireframe",0,0
#define MATKEY_BLEND_FUNC         "$mat.blend",0,0
#define MATKEY_OPACITY            "$mat.opacity",0,0
#define MATKEY_BUMPSCALING        "$mat.bumpscaling",0,0
#define MATKEY_SHININESS          "$mat.shininess",0,0
#define MATKEY_REFLECTIVITY       "$mat.reflectivity",0,0
#define MATKEY_SHININESS_STRENGTH "$mat.shinpercent",0,0
#define MATKEY_REFRACTI           "$mat.refracti",0,0
#define MATKEY_EFFECT             "$mat.effect",0,0
#define MATKEY_COLOR_DIFFUSE      "$clr.diffuse",0,0
#define MATKEY_COLOR_AMBIENT      "$clr.ambient",0,0
#define MATKEY_COLOR_SPECULAR     "$clr.specular",0,0
#define MATKEY_COLOR_EMISSIVE     "$clr.emissive",0,0
#define MATKEY_COLOR_SPHEREMAP    "$clr.spheremap",0,0
#define MATKEY_COLOR_TRANSPARENT  "$clr.transparent",0,0
#define MATKEY_COLOR_REFLECTIVE   "$clr.reflective",0,0

#define MATKEY_TEXTURE(type, N)   "$tex.file", type, N

#define MATKEY_TEXTURE_DIFFUSE(N)      MATKEY_TEXTURE(octoon::model::TextureTypeDiffuse, N)
#define MATKEY_TEXTURE_SPECULAR(N)     MATKEY_TEXTURE(octoon::model::TextureTypeSpecular, N)
#define MATKEY_TEXTURE_AMBIENT(N)      MATKEY_TEXTURE(octoon::model::TextureTypeAmbient, N)
#define MATKEY_TEXTURE_EMISSIVE(N)     MATKEY_TEXTURE(octoon::model::TextureTypeEmissive, N)
#define MATKEY_TEXTURE_NORMALS(N)      MATKEY_TEXTURE(octoon::model::TextureTypeNormals, N)
#define MATKEY_TEXTURE_HEIGHT(N)       MATKEY_TEXTURE(octoon::model::TextureTypeHeight, N)
#define MATKEY_TEXTURE_SHININESS(N)    MATKEY_TEXTURE(octoon::model::TextureTypeShininess, N)
#define MATKEY_TEXTURE_OPACITY(N)      MATKEY_TEXTURE(octoon::model::TextureTypeOpacity, N)
#define MATKEY_TEXTURE_DISPLACEMENT(N) MATKEY_TEXTURE(octoon::model::TextureTypeDisplacement, N)
#define MATKEY_TEXTURE_LIGHTMAP(N)     MATKEY_TEXTURE(octoon::model::TextureTypeLightmap, N)
#define MATKEY_TEXTURE_REFLECTION(N)   MATKEY_TEXTURE(octoon::model::TextureTypeReflection, N)

#define TEXTURE_ARRAY_COUNT 4

namespace octoon
{
	namespace model
	{
		class Animation;
		class Texture;
		class Camera;
		class Light;
		class Mesh;
		class Material;

		class Model;
		class Bone;
		class IKAttr;
		class Rigidbody;
		class Joint;
		class VertexWeight;
		class CombineMesh;

		typedef std::shared_ptr<Animation> AnimationPtr;
		typedef std::shared_ptr<Texture> TexturePtr;
		typedef std::shared_ptr<Camera> CameraPropertyPtr;
		typedef std::shared_ptr<Light> LightPropertyPtr;
		typedef std::shared_ptr<Mesh> MeshPtr;
		typedef std::shared_ptr<Material> MaterialPtr;
		typedef std::unique_ptr<class Path> PathPtr;
		typedef std::shared_ptr<class PathEdge> PathEdgePtr;
		typedef std::shared_ptr<class PathGroup> PathGroupPtr;		
		typedef std::unique_ptr<class Contour> ContourPtr;
		typedef std::shared_ptr<class ContourGroup> ContourGroupPtr;
		typedef std::shared_ptr<class TextFile> TextFilePtr;
		typedef std::shared_ptr<class TextMeshing> TextMeshingPtr;
		typedef std::shared_ptr<class ModelLoader> ModelLoaderPtr;

		typedef std::shared_ptr<Model> ModelPtr;
		typedef std::shared_ptr<Bone> BonePtr;
		typedef std::shared_ptr<IKAttr> IKAttrPtr;
		typedef std::shared_ptr<Rigidbody> RigidbodyPropertyPtr;
		typedef std::shared_ptr<Joint> JointPropertyPtr;
		typedef std::shared_ptr<VertexWeight> VertexWeightPtr;

		typedef std::vector<VertexWeight> VertexWeights;
		typedef std::vector<MeshPtr> Meshes;
		typedef std::vector<Bone> Bones;
		typedef std::vector<IKAttr> InverseKinematics;
		typedef std::vector<CombineMesh> CombineMeshes;
		typedef std::vector<TextFilePtr> TextFiles;
		typedef std::vector<ContourPtr> Contours;
		typedef std::vector<ContourGroupPtr> ContourGroups;
		typedef std::vector<PathPtr> Paths;
		typedef std::vector<PathEdge> PathEdges;
		typedef std::vector<PathGroupPtr> PathGroups;

		enum TextureType
		{
			TextureTypeNone,
			TextureTypeDiffuse,
			TextureTypeSpecular,
			TextureTypeAmbient,
			TextureTypeEmissive,
			TextureTypeHeight,
			TextureTypeNormals,
			TextureTypeShininess,
			TextureTypeOpacity,
			TextureTypeDisplacement,
			TextureTypeLightmap,
			TextureTypeReflection,
		};

		enum PropertyTypeInfo
		{
			PropertyTypeInfoFloat = 0x01,
			PropertyTypeInfoString = 0x02,
			PropertyTypeInfoInt = 0x04,
			PropertyTypeInfoBuffer = 0x08,
		};

		using istream = io::istream;
		using ostream = io::ostream;
	}
}

#endif
