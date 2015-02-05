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
//      Play loop (in-game) logic
//

#include "kexlib.h"
#include "renderMain.h"
#include "renderView.h"
#include "game.h"

//
// kexPlayLoop::kexPlayLoop
//

kexPlayLoop::kexPlayLoop(void)
{
}

//
// kexPlayLoop::~kexPlayLoop
//

kexPlayLoop::~kexPlayLoop(void)
{
}

//
// kexPlayLoop::Init
//

void kexPlayLoop::Init(void)
{
}

//
// kexPlayLoop::Start
//

void kexPlayLoop::Start(void)
{
    ticks = 0;
    
    if(kexGame::cLocal->Player()->Actor() == NULL)
    {
        kex::cSystem->Warning("No player starts present\n");
        kexGame::cLocal->SetGameState(GS_TITLE);
        return;
    }
    
    renderScene.SetView(&renderView);
    renderScene.SetWorld(kexGame::cLocal->World());

    kexGame::cLocal->Player()->Ready();
}

//
// kexPlayLoop::Stop
//

void kexPlayLoop::Stop(void)
{
    kexGame::cLocal->World()->UnloadMap();
}

//
// kexPlayLoop::Draw
//

kexCvar cvarTest("portaltest", CVF_INT, "0", " ");
kexCvar cvarTest2("testvar", CVF_INT, "0", " ");

void kexPlayLoop::Draw(void)
{
    kexPlayer *p = kexGame::cLocal->Player();
    kexWorld *world = kexGame::cLocal->World();
    
    renderView.SetupFromPlayer(p);
    world->FindVisibleSectors(renderView, p->Actor()->Sector());
    //renderScene.FindVisibleSectors(p->Actor()->Sector());

    // TEMP
    kexRender::cBackend->LoadProjectionMatrix(renderView.ProjectionView());
    kexRender::cBackend->LoadModelViewMatrix(renderView.ModelView());
    
    kexCpuVertList *vl = kexRender::cVertList;
    
    //kexRender::cTextures->defaultTexture->Bind();
    kexRender::cBackend->SetState(GLSTATE_DEPTHTEST, true);
    kexRender::cBackend->SetState(GLSTATE_ALPHATEST, true);
    kexRender::cBackend->SetState(GLSTATE_BLEND, true);
    kexRender::cBackend->SetState(GLSTATE_SCISSOR, true);

    int clipY = kex::cSystem->VideoHeight() - (int)((float)kex::cSystem->VideoHeight() / (240.0f / 24.0f));
    kexRender::cBackend->SetScissorRect(0, 0, kex::cSystem->VideoWidth(), clipY);
    
    kexTexture *skyTexture = kexRender::cTextures->Cache("textures/skies/sky_sunny.png",
                                                         TC_REPEAT, TF_NEAREST);
    skyTexture->Bind();
    //kexRender::cBackend->SetPolyMode(GLPOLY_LINE);
    vl->BindDrawPointers();
    {
        float s, c;
        float x = renderView.Origin().x;
        float y = renderView.Origin().y;
        float z = renderView.Origin().z + 1280;
        int t = 0;
        int u = 0;
        float radius = 8192;
        float height = 6144;
        float px[10], py[10], pz[10];
        float lx[10], ly[10], lz[10];
        int tris = 0;
        float ang = 0;
        
        for(int i = 0; i < 17; i++)
        {
            float z1;
            float ang2;
            
            s = kexMath::Sin(kexMath::Deg2Rad(ang));
            c = kexMath::Cos(kexMath::Deg2Rad(ang));
            
            z1 = z + height * c;
            ang += 22.5f;
            
            if(!(i % 8))
            {
                px[0] = x;
                py[0] = y + radius * s;
                pz[0] = z1;
                
                if(i != 0)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        vl->AddVertex(px[0], py[0], pz[0], 0, 0);
                        vl->AddVertex(lx[j], ly[j], lz[j], 0, 0);
                        vl->AddVertex(lx[1+j], ly[1+j], lz[1+j], 0, 0);
                        if(i == 8)
                        {
                            vl->AddTriangle(tris+2, tris+1, tris+0);
                            tris += 3;
                        }
                        else
                        {
                            vl->AddTriangle(tris+0, tris+1, tris+2);
                            tris += 3;
                        }
                    }
                }
                
                continue;
            }
            
            ang2 = 45;
            
            for(int j = 0; j < 9; j++)
            {
                float x2, y2, z2;
                
                x2 = x + kexMath::Sin(kexMath::Deg2Rad(ang2)) * radius * s;
                y2 = y + kexMath::Cos(kexMath::Deg2Rad(ang2)) * radius * s;
                z2 = z1;
                
                ang2 += 22.5f;
                
                px[1+j] = x2;
                py[1+j] = y2;
                pz[1+j] = z2;
            }
            
            if(i == 1 || i == 9)
            {
                for(int j = 0; j < 8; j++)
                {
                    vl->AddVertex(px[0], py[0], pz[0], 0, 0);
                    vl->AddVertex(px[1+j], py[1+j], pz[1+j], 0, 0);
                    vl->AddVertex(px[2+j], py[2+j], pz[2+j], 0, 0);
                    
                    if(i >= 9)
                    {
                        vl->AddTriangle(tris+2, tris+1, tris+0);
                        tris += 3;
                    }
                    else
                    {
                        vl->AddTriangle(tris+0, tris+1, tris+2);
                        tris += 3;
                    }
                }
            }
            else
            {
                float tv1 = 0.16666666666667f * (float)t;
                float tv2 = 0.16666666666667f * ((float)t+1);
                
                for(int j = 0; j < 8; j++)
                {
                    float tu1 = 0.25f * (float)u;
                    float tu2 = 0.25f * ((float)u+1);
                    
                    if(i >= 9)
                    {
                        vl->AddVertex(lx[1+j], ly[1+j], lz[1+j], 1.0f - tu2, 1.0f - tv1);
                        vl->AddVertex(lx[j], ly[j], lz[j], 1.0f - tu1, 1.0f - tv1);
                        vl->AddVertex(px[2+j], py[2+j], pz[2+j], 1.0f - tu2, 1.0f - tv2);
                        vl->AddVertex(px[1+j], py[1+j], pz[1+j], 1.0f - tu1, 1.0f - tv2);
                    }
                    else
                    {
                        vl->AddVertex(lx[j], ly[j], lz[j], 1.0f - tu1, tv1);
                        vl->AddVertex(lx[1+j], ly[1+j], lz[1+j], 1.0f - tu2, tv1);
                        vl->AddVertex(px[1+j], py[1+j], pz[1+j], 1.0f - tu1, tv2);
                        vl->AddVertex(px[2+j], py[2+j], pz[2+j], 1.0f - tu2, tv2);
                    }
                    
                    vl->AddTriangle(tris+0, tris+2, tris+1);
                    vl->AddTriangle(tris+1, tris+2, tris+3);
                    tris += 4;
                    
                    u++;
                }
                
                t = (t + 1) % 6;
            }
            
            for(int j = 0; j < 9; j++)
            {
                lx[j] = px[1+j];
                ly[j] = py[1+j];
                lz[j] = pz[1+j];
            }
        }
        
        vl->DrawElements();
    }
    //kexRender::cBackend->SetPolyMode(GLPOLY_FILL);
    kexRender::cBackend->ClearBuffer(GLCB_DEPTH);
    
    if(world->MapLoaded())
    {
        unsigned int max = cvarTest.GetInt();

        if(max == 0 || max > world->VisibleSectors().CurrentLength())
        {
            max = world->VisibleSectors().CurrentLength();
        }

        //for(unsigned int i = 0; i < world->NumSectors(); ++i)
        for(unsigned int i = 0; i < max; ++i)
        {
            mapSector_t *sector = &world->Sectors()[world->VisibleSectors()[i]];
            //mapSector_t *sector = &world->Sectors()[i];
            
            int start = sector->faceStart;
            int end = sector->faceEnd;
            int rectY;
            bool inSector = false;
            
            sector->floodCount = 0;

            if(!renderView.TestBoundingBox(sector->bounds))
            {
                continue;
            }
            
            rectY = (int)sector->y2;
            
            if(rectY > clipY)
            {
                rectY = clipY;
            }

            kexRender::cBackend->SetScissorRect((int)sector->x1, (int)sector->y1,
                (int)sector->x2, rectY);

            if(sector->flags & SF_DEBUG)
            {
                //kexRender::cUtils->DrawBoundingBox(sector->bounds, 255, 128, 0);
                sector->flags &= ~SF_DEBUG;
                inSector = true;
            }
            
            for(int j = start; j < end+3; ++j)
            {
                mapFace_t *face = &world->Faces()[j];

                if(face->flags & FF_OCCLUDED && face->sector <= -1)
                {
                    if(j <= end)
                    {
                        face->flags &= ~FF_OCCLUDED;
                        continue;
                    }
                }
                
                if(/*inSector && */face->sector != -1 && cvarTest2.GetInt() == j)
                {
                    kexRender::cUtils->DrawLine(*face->BottomEdge()->v1, *face->BottomEdge()->v2, 255, 0, 255);
                    kexRender::cUtils->DrawLine(*face->TopEdge()->v1, *face->TopEdge()->v2, 255, 0, 255);
                    kexRender::cUtils->DrawLine(*face->LeftEdge()->v1, *face->LeftEdge()->v2, 255, 0, 255);
                    kexRender::cUtils->DrawLine(*face->RightEdge()->v1, *face->RightEdge()->v2, 255, 0, 255);
                    //kex::cSystem->Printf("%i\n", j);
                }
                
                face->validcount = 0;
                
                if(face->polyStart == -1 || face->polyEnd == -1)
                {
                    continue;
                }
                
                if(!renderView.TestBoundingBox(face->bounds))
                {
                    continue;
                }
                
                if(j <= end && !face->InFront(renderView.Origin()))
                {
                    continue;
                }

                if(0 && j <= end)
                {
                    kexRender::cUtils->DrawLine(*face->BottomEdge()->v1, *face->BottomEdge()->v2, 0, 255, 0);
                    kexRender::cUtils->DrawLine(*face->TopEdge()->v1, *face->TopEdge()->v2, 0, 255, 0);
                    kexRender::cUtils->DrawLine(*face->LeftEdge()->v1, *face->LeftEdge()->v2, 0, 255, 0);
                    kexRender::cUtils->DrawLine(*face->RightEdge()->v1, *face->RightEdge()->v2, 0, 255, 0);
                }
                
                if(face->BottomEdge()->flags & EGF_TOPSTEP)
                {
                    //kexRender::cUtils->DrawLine(*face->BottomEdge()->v1, *face->BottomEdge()->v2, 0, 255, 0);
                }
                if(face->TopEdge()->flags & EGF_BOTTOMSTEP)
                {
                    //kexRender::cUtils->DrawLine(*face->TopEdge()->v1, *face->TopEdge()->v2, 255, 0, 0);
                }

                /*if(j <= end)
                {
                    kexRender::cUtils->DrawBoundingBox(face->bounds, 8, 255, 32);
                }
                else
                {
                    kexRender::cUtils->DrawBoundingBox(face->bounds, 128, 64, 255);
                }*/
                
                for(int k = face->polyStart; k <= face->polyEnd; ++k)
                {
                    int tris = 0;

                    mapPoly_t *poly = &world->Polys()[k];
                    mapTexCoords_t *tcoord = &world->TexCoords()[poly->tcoord];
                    mapVertex_t *vertex;
                    
                    int indices[4] = { 0, 0, 0, 0 };
                    int tcoords[4] = { 0, 0, 0, 0 };
                    int curIdx = 0;

                    if(world->Textures()[poly->texture])
                    {
                        world->Textures()[poly->texture]->Bind();
                    }
                    
                    for(int idx = 0; idx < 4; idx++)
                    {
                        if(poly->indices[idx] == poly->indices[(idx+1)&3])
                        {
                            continue;
                        }
                        
                        indices[curIdx] = poly->indices[idx];
                        tcoords[curIdx] = idx;
                        curIdx++;
                    }
                    
                    if(poly->flipped == 0)
                    {
                        for(int idx = 0; idx < curIdx; idx++)
                        {
                            vertex = &world->Vertices()[face->vertStart + indices[idx]];
                            
                            vl->AddVertex(vertex->origin,
                                          tcoord->uv[tcoords[idx]].s, 1.0f - tcoord->uv[tcoords[idx]].t,
                                          vertex->rgba[0],
                                          vertex->rgba[1],
                                          vertex->rgba[2],
                                          255);
                        }
                    }
                    else
                    {
                        for(int idx = (curIdx-1); idx >= 0; idx--)
                        {
                            vertex = &world->Vertices()[face->vertStart + indices[idx]];
                            
                            vl->AddVertex(vertex->origin,
                                          tcoord->uv[tcoords[idx]].s, 1.0f - tcoord->uv[tcoords[idx]].t,
                                          vertex->rgba[0],
                                          vertex->rgba[1],
                                          vertex->rgba[2],
                                          255);
                        }
                    }
                    
                    vl->AddTriangle(tris+0, tris+2, tris+1);
                    if(curIdx == 4)
                    {
                        vl->AddTriangle(tris+0, tris+3, tris+2);
                    }
                    
                    tris += curIdx;

                    vl->DrawElements();
                }
            }
        }

        if(1)
        {
            static spriteAnim_t *sprTest = NULL;

            if(sprTest == NULL)
            {
                sprTest = kexGame::cLocal->SpriteAnimManager()->Get("objects/camel_idle");
            }

            if(sprTest)
            {
                kexCpuVertList *vl = kexRender::cVertList;
                mapActor_t *a = p->Actor()->MapActor();
                kexVec3 org(a->x, a->y, a->z);
                kexMatrix mtx(renderView.Yaw(), 2);
                kexMatrix mtx2(-renderView.Pitch(), 1);
                kexMatrix mtx3 = mtx2 * mtx;
                kexMatrix scale(1.25f, 1.25f, 1.25f);
                spriteFrame_t *frame;
                spriteSet_t *spriteSet;
                kexSprite *sprite;
                spriteInfo_t *info;

                frame = &sprTest->frames[0];
                org += kexVec3(0, 0, 0);

                mtx3.RotateX(kexMath::pi);

                kexRender::cBackend->SetState(GLSTATE_SCISSOR, false);
                vl->BindDrawPointers();

                for(unsigned int i = 0; i < frame->spriteSet.Length(); ++i)
                {
                    spriteSet = &frame->spriteSet[i];
                    sprite = spriteSet->sprite;
                    info = &sprite->InfoList()[spriteSet->index];

                    float x = (float)spriteSet->x;
                    float y = (float)spriteSet->y;
                    float w = (float)info->atlas.w;
                    float h = (float)info->atlas.h;

                    float u1, u2, v1, v2;
                    
                    u1 = info->u[0 ^ spriteSet->bFlipped];
                    u2 = info->u[1 ^ spriteSet->bFlipped];
                    v1 = info->v[0];
                    v2 = info->v[1];

                    kexRender::cScreen->SetAspectDimentions(x, y, w, h);

                    sprite->Texture()->Bind();

                    kexVec3 p1 = kexVec3(x, 0, y);
                    kexVec3 p2 = kexVec3(x+w, 0, y);
                    kexVec3 p3 = kexVec3(x, 0, y+h);
                    kexVec3 p4 = kexVec3(x+w, 0, y+h);

                    p1 *= mtx3;
                    p2 *= mtx3;
                    p3 *= mtx3;
                    p4 *= mtx3;

                    p1 *= scale;
                    p2 *= scale;
                    p3 *= scale;
                    p4 *= scale;

                    p1 += org;
                    p2 += org;
                    p3 += org;
                    p4 += org;

                    vl->AddVertex(p1, u1, v1, 255, 255, 255, 255);
                    vl->AddVertex(p2, u2, v1, 255, 255, 255, 255);
                    vl->AddVertex(p3, u1, v2, 255, 255, 255, 255);
                    vl->AddVertex(p4, u2, v2, 255, 255, 255, 255);

                    vl->AddTriangle(0, 2, 1);
                    vl->AddTriangle(1, 2, 3);

                    vl->DrawElements();
                }
            }

            kexRender::cBackend->SetState(GLSTATE_SCISSOR, true);
        }

        {
            static spriteAnim_t *anim = p->Weapon().Anim();
            const kexGameLocal::weaponInfo_t *weaponInfo = kexGame::cLocal->WeaponInfo(p->CurrentWeapon());
            
            kexRender::cScreen->SetOrtho();
            kexRender::cBackend->SetState(GLSTATE_DEPTHTEST, false);
            kexRender::cBackend->SetBlend(GLSRC_SRC_ALPHA, GLDST_ONE_MINUS_SRC_ALPHA);
            
            kexRender::cBackend->SetScissorRect(0, 0, kex::cSystem->VideoWidth(), clipY);

            kexCpuVertList *vl = kexRender::cVertList;

            if(anim)
            {
                spriteFrame_t *frame = p->Weapon().Frame();
                spriteSet_t *spriteSet;
                kexSprite *sprite;
                spriteInfo_t *info;

                vl->BindDrawPointers();

                for(unsigned int i = 0; i < frame->spriteSet.Length(); ++i)
                {
                    spriteSet = &frame->spriteSet[i];
                    sprite = spriteSet->sprite;
                    info = &sprite->InfoList()[spriteSet->index];

                    float x = (float)spriteSet->x;
                    float y = (float)spriteSet->y;
                    float w = (float)info->atlas.w;
                    float h = (float)info->atlas.h;
                    word c = 0xff;

                    float u1, u2, v1, v2;
                    
                    u1 = info->u[0 ^ spriteSet->bFlipped];
                    u2 = info->u[1 ^ spriteSet->bFlipped];
                    v1 = info->v[0];
                    v2 = info->v[1];

                    kexRender::cScreen->SetAspectDimentions(x, y, w, h);

                    sprite->Texture()->Bind();

                    x += p->Weapon().BobX() + weaponInfo->offsetX;
                    y += p->Weapon().BobY() + weaponInfo->offsetY;

                    if(!(frame->flags & SFF_FULLBRIGHT))
                    {
                        c = (p->Actor()->Sector()->lightLevel << 1);

                        if(c > 255)
                        {
                            c = 255;
                        }
                    }

                    vl->AddQuad(x, y + 8, 0, w, h, u1, v1, u2, v2, (byte)c, (byte)c, (byte)c, 255);
                    vl->DrawElements();
                }
            }
        }
        
        kexRender::cBackend->SetState(GLSTATE_SCISSOR, false);
        vl->BindDrawPointers();
        
        kexTexture *gfx = kexRender::cTextures->Cache("gfx/hud.png", TC_CLAMP, TF_NEAREST);
        gfx->Bind();

        vl->AddQuad(0, 192, 0, 64, 64, 0, 0, 0.25f, 1, 255, 255, 255, 255);
        vl->AddQuad(64, 216, 0, 96, 24, 0.25f, 0, 0.625f, 0.375f, 255, 255, 255, 255);
        vl->AddQuad(160, 216, 0, 96, 24, 0.25f, 0.375f, 0.625f, 0.75f, 255, 255, 255, 255);
        vl->AddQuad(256, 192, 0, 64, 64, 0.625f, 0, 0.875f, 1, 255, 255, 255, 255);
        vl->DrawElements();
#if 0
        kexRender::cBackend->SetOrtho();
        kexRender::cTextures->whiteTexture->Bind();
        vl->BindDrawPointers();

        for(unsigned int i = 0; i < world->NumSectors(); ++i)
        {
            mapSector_t *f = &world->Sectors()[i];

            if(!renderView.TestBoundingBox(f->bounds))
            {
                continue;
            }

            if(f->flags & SF_CLIPPED)
            {
                vl->AddLine(f->x1, f->y1, 0, f->x2, f->y1, 0, 255, 0, 255, 255);
                vl->AddLine(f->x1, f->y2, 0, f->x2, f->y2, 0, 255, 0, 255, 255);
                vl->AddLine(f->x1, f->y1, 0, f->x1, f->y2, 0, 255, 0, 255, 255);
                vl->AddLine(f->x2, f->y1, 0, f->x2, f->y2, 0, 255, 0, 255, 255);
            }
            else
            {
                vl->AddLine(f->x1, f->y1, 0, f->x2, f->y1, 0, 255, 0, 0, 255);
                vl->AddLine(f->x1, f->y2, 0, f->x2, f->y2, 0, 255, 0, 0, 255);
                vl->AddLine(f->x1, f->y1, 0, f->x1, f->y2, 0, 255, 0, 0, 255);
                vl->AddLine(f->x2, f->y1, 0, f->x2, f->y2, 0, 255, 0, 0, 255);
            }
            vl->DrawLineElements();
        }
#endif
    }
}

//
// kexPlayLoop::Tick
//

void kexPlayLoop::Tick(void)
{
    if(ticks > 4)
    {
        kexGame::cLocal->UpdateActors();
        kexGame::cLocal->Player()->Tick();
    }
    
    ticks++;
}

//
// kexPlayLoop::ProcessInput
//

bool kexPlayLoop::ProcessInput(inputEvent_t *ev)
{
    return false;
}
