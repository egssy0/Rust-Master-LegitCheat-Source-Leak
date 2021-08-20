
/*bizim hook*/
#define oGameObjectManager 0x17C1F18 // GOM OFFSET

//class BasePlayer
#define oPlayerFlags 0x658 // 0x638 // public BasePlayer.PlayerFlags playerFlags;
#define oPlayerMovement 0x4E8 // 0x4D8 // public BaseMovement movement;

#define oGroundAngle 0xC4 // private float groundAngleNew;
#define oGroundAngleNew 0xC8 // private float groundAngleNew; 
#define oGravityMultiplier 0x84 // public float gravityMultiplier;
#define oFlying 0x14C // private bool flying;
#define oPlayerDistance 0x80 //public float Distance;
#define oHeld 0x98 // private EntityRef heldEntity
#define oActiveUID 0x5D0 // private uint clActiveItem;
#define oContainerBelt 0x28 // public ItemContainer containerBelt
#define oBeltContentList 0x38 // public List<Item> contents

//FOV ICIN
#define oFovConVarGraphics 0x3273160; // "Signature": "ConVar_Graphics_c*" // DONE

//Patch Debug Cam
#define oConVar_Client 0x32743D8; // "Signature": "ConVar_Client_c*" // DONE

//jump shot icin //dump.cs
#define oFlagOnGround 4//public const ModelState.Flag OnGround = 4;
#define oModelState 0x5E8 // 0x5C8 // public ModelState modelState; // 0x5C8 // DONE

//RECOIL ICIN
#define oPlayerInventory 0x668 // public PlayerInventory inventory; // 0x660
#define oPlayerActiveItem 0x5D0 // private uint clActiveItem; // 0x5C8

#define oRecoilProperties 0x2D8 // public RecoilProperties recoil; // 0x2D8
#define oRecoilYawMin 0x18  // public float recoilYawMin; // 0x18
#define oRecoilYawMax 0x1C  // public float recoilYawMax; // 0x1C
#define oRecoilPitchMin 0x20 // public float recoilPitchMin; // 0x20
#define oRecoilPitchMax 0x24 // public float recoilPitchMax; // 0x24

#define oItemListOffset 0x38 //public List<Item> itemList; // 0x38
#define oBeltOffset 0x28 // public List<PlayerInventoryProperties.ItemAmountSkinned> belt;
#define oBeltContaint 0x38
#define oEokaSuccessFraction 0x360 // public float successFraction; // 0x360
#define oFastCompoundBow 0x378	// public float stringHoldDurationMax; // 0x378
#define oCreatedProjectile 0x358 // private List<Projectile> createdProjectiles; // 0x358
#define oFastCompoundBowMoving 0x3B8 // protected float movementPenalty; // 0x3B8
#define oAutomatic 0x288 // public bool automatic;

#define oStancePenalty 0x31C //private float stancePenalty; // 0x30C
#define oAimconePenalty 0x320 //private float aimconePenalty; // 0x310
#define oAimCone 0x6C8 //public float aimCone; // 0x6B8
#define oHipAimCone 0x2EC //public float hipAimCone; // 0x2DC
#define oAimconePenaltyPerShot 0x2F0 //public float aimconePenaltyPerShot; // 0x2E0
#define oCorpsePlayerName 0x2A8// public string _playerName; // 0x2B0

#define oSparkThisFrame 0x370 // private bool _didSparkThisFrame; // 0x370
#define oAttackReady 0x360 // protected bool attackReady;
#define oArrowBack 0x364 // private float arrowBack;

#define oCamSpeed 0x2C // public static float camspeed; // 0x2C
#define oCamLerp 0x20 // public static float camlerp; // 0x20

#define oAmbientMode 0x198CB40 //// public static void set_ambientMode(AmbientMode value) { }  // 0x1857540
#define oambientIntensit 0x198CA80 //public static void set_ambientIntensity(float value) { } // 0x1857480
#define oambientLight 0x198CB00 //public static void set_ambientLight(Color value) { } // 0x1857500

#define oClothingMoveSpeedReduction 0x72C // public float clothingMoveSpeedReduction; ///////////////////////////////////////////////------------------------
#define oClothingWaterSpeedBonus 0x730 // public float clothingWaterSpeedBonus; // 0x718 ///////////////////////////////////////////////------------------------

#define oTodSky 0x11F1CD0 // public T GetComponent() { } public static TOD_Sky get_Instance() { }

#define oHeldEntity 0x98// private EntityRef heldEntity;

#define oBlockSprintOnAttack 0x299 //public bool blockSprintOnAttack;
#define oClothingBlocksAiming 0x728 // public bool clothingBlocksAiming / 0x710
#define oClothingAccuracyBonus 0x734 // public float clothingAccuracyBonus;
/**/