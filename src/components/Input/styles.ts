import styled, { css } from 'styled-components';

interface ContainerProps {
    isFocused: boolean;
}

const Container = styled.div<ContainerProps>`
    background: #f4ede8;
    border-radius: 10px;
    padding: 16px;
    width: 100%;
    display: flex;
    align-items: center;
    border: 2px solid #f4ede8;

    ${(props) => props.isFocused
    && css`
      border-color: #B0A9A8;
    `}

    input {
        flex: 1;
        background: transparent;
        border: 0;
        &::placeholder {
            color: #666360;
        }
    }
`;

export default Container;
