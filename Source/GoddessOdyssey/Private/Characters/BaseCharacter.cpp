


#include "Characters/BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	// 将 bReceivesDecals 设置为 false 表示禁用该网格组件接收贴花的功能
	GetMesh()->bReceivesDecals = false;
}

