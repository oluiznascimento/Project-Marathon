#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_FlappyBird : public olcConsoleGameEngine{
    public:
        OneLoneCoder_FlappyBird(){
            m_sAppName = L"Flappy Bird";
        }

    private:
        float fBirdPosition = 0.0f;
        float fBirdVelocity = 0.0f;
        float fBirdAcceleration = 0.0f;

        float fGravity = 100.0f;

        float fSectionWidth;
        list<int> listSection;
        float fLevelPosition = 0.0f;

        bool bHasCollided = false;
        bool bResetGame = false;

        int nAttemptCount = 0;
        int nFlapCount = 0;
        int nMaxFlapCount = 0;

    protected:
        // Chamado pelo olcConsoleGameEngine
        virtual bool OnUserCreate()
        {
            listSection = { 0, 0, 0, 0 };
            bResetGame = true;
            fSectionWidth = (float)ScreenWidth() / (float)(listSection.size() - 1);
            return true;
        }

        // Chamado pelo olcConsoleGameEngine
        virtual bool OnUserUpdate(float fElapsedTime)
        {
            if (bResetGame)
            {
                bHasCollided = false;
                bResetGame = false;
                listSection = { 0, 0, 0, 0 };
                fBirdAcceleration = 0.0f;
                fBirdVelocity = 0.0f;
                fBirdPosition = ScreenHeight() / 2.0f;
                nFlapCount = 0;
                nAttemptCount++;
            }

            // Lógica do jogo
            if (bHasCollided)
            {
                // Não faz nada até o usuário soltar a barra de espaço
                if (m_keys[VK_SPACE].bReleased)
                    bResetGame = true;
            }
            else
            {
                if (m_keys[VK_SPACE].bPressed && fBirdVelocity >= fGravity / 10.0f)
                {
                    fBirdAcceleration = 0.0f;
                    fBirdVelocity = -fGravity / 4.0f;
                    nFlapCount++;
                    if (nFlapCount > nMaxFlapCount)
                        nMaxFlapCount = nFlapCount;
                }
                else
                    fBirdAcceleration += fGravity * fElapsedTime;

                if (fBirdAcceleration >= fGravity)
                    fBirdAcceleration = fGravity;

                fBirdVelocity += fBirdAcceleration * fElapsedTime;
                fBirdPosition += fBirdVelocity * fElapsedTime;
                fLevelPosition += 14.0f * fElapsedTime;

                if (fLevelPosition > fSectionWidth)
                {
                    fLevelPosition -= fSectionWidth;
                    listSection.pop_front();
                    int i = rand() % (ScreenHeight() - 20);
                    if (i <= 10) i = 0;
                    listSection.push_back(i);
                }

                // Exibir na tela
                Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

                // Desenhar seções
                int nSection = 0;
                for (auto s : listSection)
                {
                    if (s != 0)
                    {
                        Fill(nSection * fSectionWidth + 10 - fLevelPosition, ScreenHeight() - s, nSection * fSectionWidth + 15 - fLevelPosition, ScreenHeight(), PIXEL_SOLID, FG_GREEN);
                        Fill(nSection * fSectionWidth + 10 - fLevelPosition, 0, nSection * fSectionWidth + 15 - fLevelPosition, ScreenHeight() - s - 15, PIXEL_SOLID, FG_GREEN);
                    }
                    nSection++;
                }

                int nBirdX = (int)(ScreenWidth() / 3.0f);

                // Detecção de colisão
                bHasCollided = fBirdPosition < 2 || fBirdPosition > ScreenHeight() - 2 ||
                    m_bufScreen[(int)(fBirdPosition + 0) * ScreenWidth() + nBirdX].Char.UnicodeChar != L' ' ||
                    m_bufScreen[(int)(fBirdPosition + 1) * ScreenWidth() + nBirdX].Char.UnicodeChar != L' ' ||
                    m_bufScreen[(int)(fBirdPosition + 0) * ScreenWidth() + nBirdX + 6].Char.UnicodeChar != L' ' ||
                    m_bufScreen[(int)(fBirdPosition + 1) * ScreenWidth() + nBirdX + 6].Char.UnicodeChar != L' ';

                // Desenhar pássaro
                if (fBirdVelocity > 0)
                {
                    DrawString(nBirdX, fBirdPosition + 0, L"\\\\\\");
                    DrawString(nBirdX, fBirdPosition + 1, L"<\\\\\\=Q");
                }
                else
                {
                    DrawString(nBirdX, fBirdPosition + 0, L"<///=Q");
                    DrawString(nBirdX, fBirdPosition + 1, L"///");
                }

                DrawString(1, 1, L"Tentativa: " + to_wstring(nAttemptCount) + L" Pontuação: " + to_wstring(nFlapCount) + L" Pontuação Máxima: " + to_wstring(nMaxFlapCount));
            }

            return true;
        }
};

int main(){
    OneLoneCoder_FlappyBird game;
    game.ConstructConsole(80, 48, 16, 16);
    game.Start();

    return 0;
}
