import React, { useState } from 'react';
import { FiPlus } from 'react-icons/fi';

import { Container, ResumedData, AddXBI } from './styles';

type CardProps = {
    basePicture: string | null;
    targetPicture: string | null;
    imageDiff: number;
    chiSquared: number;
    phash: number;
    positionLeft: number;
    positionRight: number;
    positionY: number;
    visibilityLeft: number;
    visibilityRight: number;
    widthComparison: number;
    heightComparison: number;
    addFunction(): boolean;
    setVisible(visible: boolean): void,
    setBasePicture(pictureUrl: string): void,
    setTargetPicture(pictureUrl: string): void,
  };

const Card: React.FC<CardProps> = ({
    basePicture,
    targetPicture,
    imageDiff,
    chiSquared,
    phash,
    positionLeft,
    positionRight,
    positionY,
    visibilityLeft,
    visibilityRight,
    widthComparison,
    heightComparison,
    addFunction,
    setVisible,
    setBasePicture,
    setTargetPicture,
}) => {
    const [added, setAdded] = useState(false);

    const handleAddedItem = () => {
        const addedItem = addFunction();

        setAdded(addedItem);
    };

    const setPictures = () => {
        setBasePicture(basePicture || 'https://www.biotecdermo.com.br/wp-content/uploads/2016/10/sem-imagem-10.jpg');
        setTargetPicture(targetPicture || 'https://www.biotecdermo.com.br/wp-content/uploads/2016/10/sem-imagem-10.jpg');

        setVisible(true);
    };

    return (
        <Container>
            <span>Referência: </span>
            <img src={basePicture || 'https://www.biotecdermo.com.br/wp-content/uploads/2016/10/sem-imagem-10.jpg'} alt="xbi" />
            <span>Destino: </span>
            <img src={targetPicture || 'https://www.biotecdermo.com.br/wp-content/uploads/2016/10/sem-imagem-10.jpg'} alt="xbi" />

            <button type="button" onClick={setPictures}>Comparar</button>

            <ResumedData>
                <span>
                    Image Diff:
                    {' '}
                    {imageDiff}
                </span>
                <span>
                    Distância χ2:
                    {' '}
                    {chiSquared}
                </span>
                <span>
                    Distância pHash:
                    {' '}
                    {phash}
                </span>
                <span>
                    Posição direita:
                    {' '}
                    {positionLeft}
                </span>
                <span>
                    Posição esquerda:
                    {' '}
                    {positionRight}
                </span>
                <span>
                    Posição altura:
                    {' '}
                    {positionY}
                </span>
                <span>
                    Visibilidade esquerda:
                    {' '}
                    {visibilityLeft}
                </span>
                <span>
                    Visibilidade direita:
                    {' '}
                    {visibilityRight}
                </span>
                <span>
                    Largura:
                    {' '}
                    {widthComparison}
                </span>
                <span>
                    Altura:
                    {' '}
                    {heightComparison}
                </span>
            </ResumedData>

            <AddXBI added={added} onClick={handleAddedItem}><FiPlus color="white" size={32} /></AddXBI>
        </Container>
    );
};

export default Card;
