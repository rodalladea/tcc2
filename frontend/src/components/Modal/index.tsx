import React from 'react';
import { FiPlus } from 'react-icons/fi';
import {
    ModalContainer,
    Background,
    ModalContent,
    CloseButton,
} from './styles';

interface ModalProps {
    visible: boolean;
    setVisible(visible: boolean): void;
    basePicture: string;
    targetPicture: string;
}

const Modal: React.FC<ModalProps> = ({
    visible, setVisible, basePicture, targetPicture,
}) => {
    const closeModal = () => {
        setVisible(false);
    };

    return (
        <Background visible={visible}>
            <ModalContainer visible={visible}>
                <CloseButton onClick={closeModal}><FiPlus color="white" size={58} /></CloseButton>
                <ModalContent>
                    <img src={basePicture} alt="referencia" />
                    <img src={targetPicture} alt="destino" />
                </ModalContent>
            </ModalContainer>
        </Background>
    );
};

export default Modal;
