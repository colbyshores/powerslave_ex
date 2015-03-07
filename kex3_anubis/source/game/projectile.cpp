//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Projectile Object
//

#include "kexlib.h"
#include "game.h"

//-----------------------------------------------------------------------------
//
// kexProjectile
//
//-----------------------------------------------------------------------------

DECLARE_KEX_CLASS(kexProjectile, kexActor)

//
// kexProjectile::kexProjectile
//

kexProjectile::kexProjectile(void)
{
    this->damage = 0;
    this->projectileFlags = 0;
    this->homingTurnAngles = 0.03125f;
    this->homingMaxPitch = 0.25f;
    this->homingMaxSightDistance = 2000;
    this->homingActor = NULL;
}

//
// kexProjectile::~kexProjectile
//

kexProjectile::~kexProjectile(void)
{
    SetHomingTarget(NULL);
}

//
// kexProjectile::Tick
//

void kexProjectile::Tick(void)
{
    kexActor::Tick();

    if(projectileFlags & PF_HOMING)
    {
        HomingThink();
    }
}

//
// kexProjectile::SetHomingTarget
//

void kexProjectile::SetHomingTarget(kexActor *actor)
{
    // If there was a target already, decrease its refcount
    if(homingActor)
    {
        homingActor->RemoveRef();
    }

    // Set new target and if non-NULL, increase its counter
    if((homingActor = actor))
    {
        homingActor->AddRef();
    }
}

//
// kexProjectile::HomingThink
//

void kexProjectile::HomingThink(void)
{
    if(homingActor != NULL)
    {
        if(homingActor->Removing() || homingActor->Health() <= 0)
        {
            SetHomingTarget(NULL);
            return;
        }

        kexVec3 vOrigin = homingActor->Origin() + kexVec3(0, 0, homingActor->Height() * 0.5f);
        kexVec3 dir = (vOrigin - origin).Normalize();
        kexAngle an1 = dir.ToYaw();

        kexAngle diff = an1 - yaw;

             if(diff.an >  homingTurnAngles) yaw += homingTurnAngles;
        else if(diff.an < -homingTurnAngles) yaw -= homingTurnAngles;
        else yaw = an1;
        
        pitch = -dir.ToPitch();
        kexMath::Clamp(pitch.an, -homingMaxPitch, homingMaxPitch);
    }
    else if(!RandomDecision(14))
    {
        SeekTargets();
    }
}

//
// kexProjectile::AdjustAlongFace
//

void kexProjectile::AdjustAlongFace(mapFace_t *face)
{
    if(face->flags & FF_WATER)
    {
        return;
    }

    if(kexMath::Fabs(face->plane.c) <= 0.5f)
    {
        // explode on steep slopes
        OnImpact(NULL);
        return;
    }

    float len = velocity.Unit();

    kexVec3 forward;
    kexVec3::ToAxis(&forward, 0, 0, yaw, 0, 0);

    pitch = face->plane.ToPitch();
    if(face->plane.c < 0)
    {
        pitch += kexMath::pi;
    }

    if(!face->plane.IsFacing(yaw))
    {
        pitch = -pitch;
    }

    velocity = forward * len;
}

//
// kexProjectile::SeekTargets
//

void kexProjectile::SeekTargets(void)
{
    kexVec3 start = origin + kexVec3(0, 0, height * 0.5f);
    kexVec3 end;
    kexStack<mapSector_t*> *sectorList;

    sectorList = kexGame::cLocal->World()->FloodFill(start, sector, homingMaxSightDistance);

    for(unsigned int i = 0; i < sectorList->CurrentLength(); ++i)
    {
        for(kexActor *actor = (*sectorList)[i]->actorList.Next();
            actor != NULL;
            actor = actor->SectorLink().Next())
        {
            if(actor == this || actor == target ||
                actor->Health() <= 0 || !(actor->Flags() & AF_SHOOTABLE) ||
                !actor->InstanceOf(&kexAI::info))
            {
                continue;
            }

            if(kexMath::Fabs(origin.x - actor->Origin().x) >= homingMaxSightDistance) continue;
            if(kexMath::Fabs(origin.y - actor->Origin().y) >= homingMaxSightDistance) continue;

           
            end = actor->Origin() + kexVec3(0, 0, actor->Height() * 0.5f);

            if(kexGame::cLocal->CModel()->Trace(this, sector, start, end, radius*2, false))
            {
                continue;
            }

            SetHomingTarget(actor);

            if((kexRand::Int() & 7) == 3)
            {
                return;
            }
        }
    }
}

//
// kexProjectile::UpdateVelocity
//

void kexProjectile::UpdateVelocity(void)
{
    // check for drop-offs
    if(origin.z > floorHeight)
    {
        velocity.z -= gravity;
    }
}

//
// kexProjectile::CheckFloorAndCeilings
//

void kexProjectile::CheckFloorAndCeilings(void)
{
    kexVec3 position = (origin + velocity);

    if(sector->ceilingFace->flags & FF_SOLID)
    {
        kexPlane::planeSide_t ceilingSide;
        ceilingSide = sector->ceilingFace->plane.PointOnSide(position + kexVec3(0, 0, height));
        // bump ceiling
        if(ceilingSide == kexPlane::PSIDE_BACK || ceilingSide == kexPlane::PSIDE_ON)
        {
            if(projectileFlags & PF_IMPACTWALLSONLY)
            {
                AdjustAlongFace(sector->ceilingFace);
            }
            else
            {
                OnImpact(NULL);
            }
            return;
        }
    }
    
    if(sector->floorFace->flags & FF_SOLID)
    {
        kexPlane::planeSide_t floorSide;
        floorSide = sector->floorFace->plane.PointOnSide(position);
        // bump floor
        if(floorSide == kexPlane::PSIDE_BACK || floorSide == kexPlane::PSIDE_ON)
        {
            if(projectileFlags & PF_IMPACTWALLSONLY)
            {
                AdjustAlongFace(sector->floorFace);
            }
            else
            {
                OnImpact(NULL);
            }
            return;
        }
    }

    kexActor::CheckFloorAndCeilings();
}

//
// kexProjectile::UpdateMovement
//

void kexProjectile::UpdateMovement(void)
{
    kexActor::UpdateMovement();

    if(kexGame::cLocal->CModel()->Fraction() != 1)
    {
        OnImpact(kexGame::cLocal->CModel()->ContactActor());
    }

    if(velocity.UnitSq() <= 0.05f)
    {
        OnImpact(NULL);
        return;
    }

    if(!kexGame::cLocal->CModel()->PointWithinSectorEdges(origin, sector))
    {
        kex::cSystem->Warning("Projectile (type %i) out of sector bounds\n", type);
        OnImpact(NULL);
    }

}

//
// kexProjectile::OnImpact
//

void kexProjectile::OnImpact(kexActor *contactActor)
{
    if(projectileFlags & PF_IMPACTED)
    {
        return;
    }

    if(contactActor && damage > 0)
    {
        contactActor->InflictDamage(this, damage);
    }

    if(flags & AF_INWATER && deathWaterAnim)
    {
        ChangeAnim(deathWaterAnim);
    }
    else
    {
        ChangeAnim(deathAnim);
    }

    SetHomingTarget(NULL);

    flags &= ~(AF_MOVEABLE|AF_SOLID);
    projectileFlags |= PF_IMPACTED;
}

//
// kexProjectile::Spawn
//

void kexProjectile::Spawn(void)
{
    if(definition)
    {
        definition->GetInt("damage", damage, 0);
        definition->GetFloat("homingTurnAngles", homingTurnAngles, 0.03125f);
        definition->GetFloat("homingMaxPitch", homingMaxPitch, 0.25f);
        definition->GetFloat("homingMaxSightDistance", homingMaxSightDistance, 2000);

        if(definition->GetBool("impactWallsOnly"))  projectileFlags |= PF_IMPACTWALLSONLY;
        if(definition->GetBool("homing"))           projectileFlags |= PF_HOMING;
    }
}

//-----------------------------------------------------------------------------
//
// kexProjectileFlame
//
//-----------------------------------------------------------------------------

DECLARE_KEX_CLASS(kexProjectileFlame, kexProjectile)

//
// kexProjectileFlame::kexProjectileFlame
//

kexProjectileFlame::kexProjectileFlame(void)
{
    this->fizzleTime = 0;
    this->lifeTime = 50;
}

//
// kexProjectileFlame::~kexProjectileFlame
//

kexProjectileFlame::~kexProjectileFlame(void)
{
}

//
// kexProjectileFlame::Tick
//

void kexProjectileFlame::Tick(void)
{
    float lt = (float)lifeTime;

    if(Removing())
    {
        return;
    }
    
    if(flags & AF_INWATER)
    {
        Remove();
        return;
    }

    kexProjectile::Tick();

    if(anim == deathAnim)
    {
        return;
    }

    fizzleTime += 0.5f;
    scale += ((5000 - ((fizzleTime * 65536) / 512)) / 128) / 512;

    if(fizzleTime < lt * 0.5f)
    {
        color.Lerp(kexVec3(1.0f, 1.0f, 0.25f), 1.0f / (lt * 0.5f));
    }
    else
    {
        color.Lerp(kexVec3(1.0f, 0.25f, 0.0625f), 1.0f / (lt * 0.5f));
    }

    if(fizzleTime >= lt)
    {
        Remove();
    }
}

//
// kexProjectileFlame::OnImpact
//

void kexProjectileFlame::OnImpact(kexActor *contactActor)
{
    if(contactActor && contactActor->InstanceOf(&kexAI::info))
    {
        static_cast<kexAI*>(contactActor)->Ignite(this);
    }

    kexProjectile::OnImpact(contactActor);
}

//
// kexProjectileFlame::Spawn
//

void kexProjectileFlame::Spawn(void)
{
    if(definition)
    {
        definition->GetInt("lifeTime", lifeTime, 50);
    }

    fizzleTime = 0;
}

//-----------------------------------------------------------------------------
//
// kexFireballSpawner
//
//-----------------------------------------------------------------------------

DECLARE_KEX_CLASS(kexFireballSpawner, kexActor)

//
// kexProjectile::kexProjectile
//

kexFireballSpawner::kexFireballSpawner(void)
{
    this->fireDelay = 50;
    this->bEnabled = false;
}

//
// kexFireballSpawner::~kexFireballSpawner
//

kexFireballSpawner::~kexFireballSpawner(void)
{
}

//
// kexFireballSpawner::Tick
//

void kexFireballSpawner::Tick(void)
{
    if(Removing())
    {
        return;
    }

    if(mapActor == NULL)
    {
        Remove();
        return;
    }

    kexActor::Tick();

    if(!bEnabled)
    {
        return;
    }

    fireDelay -= 0.5f;

    if(fireDelay <= 0)
    {
        bEnabled = false;

        mapFace_t *face = &kexGame::cLocal->World()->Faces()[mapActor->params2];
        mapPoly_t *poly = &kexGame::cLocal->World()->Polys()[mapActor->params1];
        SpawnFireball(face, poly);
    }
}

//
// kexFireballSpawner::SpawnFireball
//

void kexFireballSpawner::SpawnFireball(mapFace_t *face, mapPoly_t *poly)
{
    mapVertex_t *v = kexGame::cLocal->World()->Vertices();
    int secID, projType;
    float speed;
    int avg = 0;
    kexVec3 vOrigin;
    kexVec3 vFaceOrg;
    kexActor *proj;

    secID = sector - kexGame::cLocal->World()->Sectors();

    for(int i = face->polyStart; i <= face->polyEnd; ++i)
    {
        mapPoly_t *p = &kexGame::cLocal->World()->Polys()[i];

        if(p->texture != poly->texture)
        {
            continue;
        }

        vFaceOrg += v[face->vertStart + p->indices[0]].origin;
        vFaceOrg += v[face->vertStart + p->indices[1]].origin;
        vFaceOrg += v[face->vertStart + p->indices[2]].origin;

        avg += 3;
    }
    
    vOrigin = (v[face->vertStart + poly->indices[0]].origin +
               v[face->vertStart + poly->indices[1]].origin +
               v[face->vertStart + poly->indices[2]].origin) / 3;

    if(avg > 0)
    {
        vFaceOrg /= (float)avg;
        vOrigin.Lerp(vFaceOrg, 0.5f);
    }

    vOrigin += (face->plane.Normal() * 32);

    switch(type)
    {
    case AT_FIREBALLSPAWNER:
        kexGame::cLocal->SpawnActor(AT_FIREBALLPUFF, vOrigin.x, vOrigin.y, vOrigin.z, 0, secID);
        projType = AT_FIREBALL;
        speed = 8;
        break;

    case AT_LASERSPAWNER:
        projType = AT_LASER;
        speed = 16;
        break;

    default:
        return;
    }

    proj = kexGame::cLocal->SpawnActor(projType,
                                       vOrigin.x, vOrigin.y, vOrigin.z,
                                       face->plane.Normal().ToYaw(),
                                       secID);

    if(proj == NULL)
    {
        return;
    }

    proj->SetTarget(this);
    proj->Velocity() = (face->plane.Normal() * speed);
    proj->PlaySound("sounds/fballshoot.wav");
}

//
// kexFireballSpawner::OnActivate
//

void kexFireballSpawner::OnActivate(kexActor *instigator)
{
    bEnabled = true;
}

//
// kexFireballSpawner::OnDeactivate
//

void kexFireballSpawner::OnDeactivate(kexActor *instigator)
{
    bEnabled = false;
}

//
// kexFireballSpawner::Spawn
//

void kexFireballSpawner::Spawn(void)
{
    flags |= AF_HIDDEN;
}

//-----------------------------------------------------------------------------
//
// kexFireballFactory
//
//-----------------------------------------------------------------------------

DECLARE_KEX_CLASS(kexFireballFactory, kexGameObject)

//
// kexProjectile::kexProjectile
//

kexFireballFactory::kexFireballFactory(void)
{
    this->intervals = 60;
    this->currentTime = 0;
    this->fireballType = -1;
    this->extraDelay = 0;
    this->sector = NULL;
}

//
// kexFireballFactory::~kexFireballFactory
//

kexFireballFactory::~kexFireballFactory(void)
{
}

//
// kexFireballFactory::Remove
//

void kexFireballFactory::Remove(void)
{
    for(kexActor *actor = sector->actorList.Next();
        actor != NULL;
        actor = actor->SectorLink().Next())
    {
        if(actor->MapActor() == NULL)
        {
            continue;
        }

        if(actor->MapActor()->type != fireballType)
        {
            continue;
        }

        actor->OnDeactivate(NULL);
    }

    sector->flags &= ~SF_SPECIAL;
    sector->objectThinker = NULL;
    kexGameObject::Remove();
}

//
// kexFireballFactory::Tick
//

void kexFireballFactory::Tick(void)
{
    float fireDelay = extraDelay;

    if(sector == NULL)
    {
        Remove();
        return;
    }

    currentTime += 0.5f;

    if(currentTime >= intervals)
    {
        currentTime = 0;

        for(kexActor *actor = sector->actorList.Next();
            actor != NULL;
            actor = actor->SectorLink().Next())
        {
            if(actor->MapActor() == NULL)
            {
                continue;
            }

            if(actor->MapActor()->type != fireballType)
            {
                continue;
            }

            actor->OnActivate(NULL);
            if(actor->InstanceOf(&kexFireballSpawner::info))
            {
                static_cast<kexFireballSpawner*>(actor)->fireDelay = fireDelay;
                fireDelay += 8;
            }
        }
    }
}

//
// kexFireballFactory::Spawn
//

void kexFireballFactory::Spawn(void)
{
    switch(fireballType)
    {
    case AT_FIREBALLSPAWNER:
        intervals = 60;
        break;

    case AT_LASERSPAWNER:
        intervals = 10;
        break;

    default:
        break;
    }

    currentTime = intervals;
}

//
// kexFireballFactory::SetSector
//

void kexFireballFactory::SetSector(mapSector_t *s)
{
    sector = s;
    sector->flags |= SF_SPECIAL;
    sector->objectThinker = this;
}
