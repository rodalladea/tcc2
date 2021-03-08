import styled, { css } from 'styled-components';

interface AddXBIProps {
    added: boolean;
  }

export const Container = styled.div`
    padding: 16px;
    box-shadow: 3px 3px 16px 6px #ccc;
    width: 320px;
    border-radius: 10px;
    position: relative;
    margin: 16px;

    img {
        width: 100%;
        border-radius: 10px;
        margin-bottom: 16px;
    }

    button {
        width: 100%;
        margin: 0 0 16px 0;
    }
`;

export const ResumedData = styled.div`
    display: flex;
    flex-direction: column;

    span {
        margin-bottom: 4px;
    }
`;

export const AddXBI = styled.div<AddXBIProps>`
    display: flex;
    justify-content: center;
    align-items: center;

    position: absolute;
    right: -24px;
    bottom: -24px;
    width: 64px;
    height: 64px;
    border-radius: 50%;
    cursor: pointer;
    transition: transform .25s;
    ${(props) => (props.added ? css`background: #F75348; transform: rotate(405deg);` : css`background: #3AB503;`)}

    &:hover {
        ${(props) => (props.added ? css`background: #C34139; transform: rotate(405deg);` : css`background: #257202;`)}
    }
`;
