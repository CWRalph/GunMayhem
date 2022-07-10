//Find closest player
		for (auto& pla : players)
		{
			if (!(pla == *p))
			{
				ylen = p->GetCenterPos().y - pla.GetCenterPos().y;
				xlen = p->GetCenterPos().x - pla.GetCenterPos().x;
				float currentHypotenuse = sqrtf(pow(ylen, 2) + pow(xlen, 2));
				if (abs(currentHypotenuse) < abs(minDistance))
				{
					minDistance = currentHypotenuse;
					pindex = iterator;
					minXlen = xlen;
					minYlen = ylen;
				}
			}
			++iterator;

			if (p->runToCenter < 0.f)
			{
				if (CheckCollisionRecs(p->GetCollider(), pla.GetCollider()))
					p->runToCenter = 1.f;
			}
			else
				p->runToCenter -= dt;
		}

		if ((abs(minXlen) < 300.f || titleScreen) && p->GetCollider().y > 0.f)
			if (abs(minYlen) < HITBOX_HEIGHT * 1.2f)
				shoot = true;

		if (p->runToCenter <= 0.f && minYlen > HITBOX_HEIGHT * 1.1f)
		{
			if (p->GetOnPlatform())
				p->Jump();	
			else if (p->GetVerticalVelocity() > -30.f)	
				p->Jump();	

		}

		iterator = 0;
		if (minXlen < 0) p->SetDirection(Direction::Right);
		else p->SetDirection(Direction::Left);
		float x = (textures[p->GetGun().GetName()].width * p->GetScale()) + textures[p->GetGun().GetName()].width * 0.33f;

		short platformIndex = 0;
		minYlen = screenHeight;
		if (p->GetDirection() == Direction::Left) x *= -1;
		//Shoot if you can hit the person
		for (const auto& pl : levels[currentLevelKey].getPlatforms())
		{
			if (!drop && p->getNextYPos() + p->GetCollider().height < pl.y)
				if (p->GetOnPlatform() && p->WithinHorizontalPosition(pl, true) && minYlen < HITBOX_HEIGHT * 1.1f)
				{
					p->Drop();
					drop = true;
				}
			if (p->WithinHorizontalPosition(pl))
			{				
				if (pl.y - p->GetCollider().x > -1.f && pl.y - p->GetCollider().x < minYlen)
				{
					platformIndex = iterator;
					minYlen = pl.y - p->GetCollider().x;
				}					
			}
			++iterator;
			if (p->runAwayTimer <= 0.f && (p->GetCollider().x < 50.f || p->GetCollider().x > screenWidth - 50.f))
				p->runAwayTimer = 0.63f;
			else
				p->runAwayTimer = 0.f;
							
			if (p->runAwayTimer > 0.f && !runToCenter)
			{				
				if (p->GetCollider().x > screenWidth * 0.5f)
				{
					p->SetDirection(Direction::Left);
					if (WithinHorizontalPosition(pl, { p->getNextXPos() * 1.1f, p->GetCollider().width }))
						runToCenter = true;

				}
				else
				{
					p->SetDirection(Direction::Right);
					if (WithinHorizontalPosition(pl, { p->getNextXPos() * 1.1f, p->GetCollider().width }))
						runToCenter = true;
				}

				if (runToCenter)
				{
					if (p->GetCollider().y > pl.y + 50)
						runToCenter = false;
					else if (p->GetCollider().y > pl.y)
						jump = true;
				}
			}							
		}

		

		if (p->runAwayTimer > 0.f)
		{
			if (runToCenter)
			{
				p->runAwayTimer -= dt;
				if (p->GetDirection() == Direction::Left)
					p->MoveLeft();
				else
					p->MoveRight();

				if (jump)
				{
					if (p->GetOnPlatform())
						p->Jump();
					else if (p->GetVerticalVelocity() > -30.f)
						p->Jump();
				}				
			}			
		}				
		else if (shoot)
		{
			if (((p->GetGun().GetBullet().getSpeed() * dt) * (p->GetGun().GetBullet().getLifespan() / dt)) + textures[p->GetGun().GetName()].width + 60 >= minDistance)				
				p->Shoot();
			if (p->runAwayTimer >= 0.f || Random(15) < 1)
			{
				if (p->runAwayTimer >= 0.f)
				{
					if (p->GetSpeedScale() > 1.f) 
						p->SetSpeedScale(1.15f);				
				}
				if (p->GetDirection() == Direction::Left && p->GetCollider().x > -50.f)
					if (p->GetCollider().x + 10.f > levels[currentLevelKey].getPlatforms()[platformIndex].x) p->MoveLeft();
				else if (p->GetCollider().x < screenWidth + 50.f)
					if (p->GetCollider().x + 10.f < levels[currentLevelKey].getPlatforms()[platformIndex].x)
						p->MoveRight();
			}				
		}
		else if (p->runAwayTimer >= 0.f || WithinHorizontalPosition(levels[currentLevelKey].getPlatforms()[platformIndex], { p->getNextXPos() * 1.5f, p->GetCollider().width }))
		{
			if (p->runAwayTimer >= 0.f)
			{
				if (p->GetSpeedScale() > 1.f)
					p->SetSpeedScale(1.15f);
			}
			if (p->GetDirection() == Direction::Left && p->GetCollider().x > -50.f)
				p->MoveLeft();
			else if (p->GetCollider().x < screenWidth + 50.f)
				p->MoveRight();
		}