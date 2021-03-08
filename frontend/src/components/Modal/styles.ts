import styled, { css, keyframes } from 'styled-components';

interface ModalStyleInterface {
    visible: boolean;
}

export const Background = styled.div<ModalStyleInterface>`
  ${({ visible }) => (visible
        ? css`
          display: block;
        `
        : css`
          display: none;
        `)}
  position: fixed;
  top: 0;
  width: 100%;
  height: 100%;
  z-index: 10;
  background: #00000066;
`;

const appearFromTop = keyframes`
  from {
    opacity: 0;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -200%);
  }
  to {
    opacity: 1;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
`;

export const ModalContainer = styled.div<ModalStyleInterface>`
  ${({ visible }) => (visible
        ? css`
          display: block;
        `
        : css`
          display: none;
        `)}
  position: fixed;
  background: transparent;
  top: 50%;
  left: 50%;
  width: 100%;
  height: 100%;
  transform: translate(-50%, -50%);
  animation: ${appearFromTop} 1s;
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 20;
`;

export const ModalContent = styled.div`
  margin: 16px;
  display: flex;
  align-items: center;
  justify-content: center;
  overflow: visible;

  img {
      margin: 8px 8px;
      max-width: 100%;
  }
`;

export const CloseButton = styled.button`
  background: transparent;
  border: none;
  transform: rotate(45deg);
  position: fixed;
  top: 16px;
  left: 16px;
`;
