import styled from 'styled-components';

export const Header = styled.header`
    width: 100%;
    height: 72px;
    background: #f0f0f0;
    box-shadow: 3px 3px 16px 6px #ccc;

    display: flex;
    justify-content: space-between;
    align-items: center;

    h1 {
        margin-left: 16px;
        font-size: 24px;
    }

    div {
        display: flex;
        justify-content: center;
        align-items: center;

        button {
            margin: 0 16px;
            padding: 12px 16px;
            border-radius: 10px;
            border: none;
            background: #F75348;
            color: #e0e0e0;
            &:hover {
                background: #C34139;
            }
        }
    }
`;

export const ProfileImage = styled.img`
    width: 40px;
    height: 40px;
    border-radius: 50%;
`;

export const Content = styled.div`
    display: flex;
    flex-direction: column;
    align-items: center;
    margin: 32px 32px;

    button {
        margin: 32px;
        padding: 16px;
        border: 1px solid #D4CCCB;
        background: transparent;
        border-radius: 10px;
        font-weight: 400;
        font-size: 32px;
        color: #545050;

        &:hover {
            background: #EBE2E1;
        }
    }

    form {
        display: flex;
        justify-content: center;
        align-items: center;
        margin-bottom: 32px;

        height: 56px;
        width: 100%;
        max-width: 800px;

        button {
            margin-left: 8px;
            width: 88px;
            height: 100%;
            border-radius: 10px;
            border: none;
            font-size: 18px;
            font-weight: 500;
            background: #EBE2E1;

            &:hover {
                background: #D4CCCB;
            }
        }
    }
`;

export const DownloadButton = styled.a`
    border: 1px solid #00B2FF;
    padding: 8px;
    border-radius: 5px;
    color: #00B2FF;
    margin-bottom: 16px;
    text-decoration: none;

    &:hover {
        background: #D8F3FF;
    }
`;

export const AllCards = styled.div`
    display: flex;
    justify-content: flex-start;
    flex-wrap: wrap;

    width: 100%;
`;
