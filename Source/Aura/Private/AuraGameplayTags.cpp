// Copyright, Wisle25

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitNativeGameplayTags()
{
    // * Primary Attributes * //
    GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Primary.Strength");
    GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Primary.Intelligence");    
    GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Primary.Resilience");    
    GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Primary.Vigor");  

    // * Secondary Attributes * //
    GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.Armor");
    GameplayTags.Attributes_Secondary_ArmorPen = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.ArmorPen");    
    GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.BlockChance");    
    GameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.CritChance");    
    GameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.CritDamage");    
    GameplayTags.Attributes_Secondary_CritRes = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.CritRes");    
    GameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.HealthRegen");    
    GameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.ManaRegen");    
    GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.MaxHealth");    
    GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get()
        .AddNativeGameplayTag("Attributes.Secondary.MaxMana");    
}
