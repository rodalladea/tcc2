import React, { useCallback, useState } from 'react';

import {
    Header, Content, AllCards, DownloadButton,
} from './styles';

import Input from '../../components/Input';
import Card from '../../components/Card';
import Modal from '../../components/Modal';
import api from '../../api';

interface XBIdataInterface {
    id: string;
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
}

interface AllXBIDataInterface {
    arffFile: string;
    allData: Array<XBIdataInterface>;
}

const Home: React.FC = () => {
    const [typedSite, setTypedSite] = useState('');
    const [allXBIData, setAllXBIData] = useState<AllXBIDataInterface>({} as AllXBIDataInterface);
    const [added, setAdded] = useState([] as Array<XBIdataInterface>);
    const [arffFile, setArffFile] = useState('');
    const [loading, setLoading] = useState(false);
    const [visible, setVisible] = useState(false);
    const [basePicture, setBasePicture] = useState('');
    const [targetPicture, setTargetPicture] = useState('');

    const collector = useCallback(async (e): Promise<void> => {
        e.preventDefault();

        setLoading(true);

        const response = await api.post('/collector', {
            typedSite,
        });

        setLoading(false);

        setArffFile(response.data.arffFile);
        setAllXBIData(response.data);
    }, [typedSite]);

    const sendXBIs = useCallback(async (e): Promise<void> => {
        e.preventDefault();

        await api.post('/saveXBIs', {
            data: {
                arffFile,
                XBIs: added,
            },
        });

        setAllXBIData({} as AllXBIDataInterface);
    }, [added, arffFile]);

    const addXBI = useCallback((XBI: XBIdataInterface): boolean => {
        const addedAux = [...added];

        if (addedAux.find((item) => item.id === XBI.id)) {
            const index = addedAux.findIndex((item) => item.id === XBI.id);
            addedAux.splice(index, 1);
            setAdded(addedAux);
            return false;
        }
        addedAux.push(XBI);

        setAdded(addedAux);

        return true;
    }, [added]);

    return (
        <>
            <Header>
                <h1>Collector</h1>
                {/* <div>
                    <ProfileImage src="https://thumbs.dreamstime.com/b/default-avatar-profile-trendy-style-social-media-user-icon-187599373.jpg" alt="user" />
                    <h1>Usuário</h1>
                    <button type="button">Sair</button>
                </div> */}
            </Header>
            <Content>
                <form onSubmit={collector}>
                    <Input
                        placeholder="Insira seu site"
                        onChange={(e) => setTypedSite(e.target.value)}
                    />
                    <button type="submit">Enviar</button>
                </form>
                {allXBIData.arffFile ? (
                    <>
                        <DownloadButton href={allXBIData.arffFile}>
                            Download arquivo ARFF
                        </DownloadButton>
                        <AllCards>
                            {
                                allXBIData.allData.map((XBIData) => (
                                    <Card
                                        basePicture={XBIData.basePicture}
                                        targetPicture={XBIData.targetPicture}
                                        imageDiff={XBIData.imageDiff}
                                        chiSquared={XBIData.chiSquared}
                                        phash={XBIData.phash}
                                        positionLeft={XBIData.positionLeft}
                                        positionRight={XBIData.positionRight}
                                        positionY={XBIData.positionY}
                                        visibilityLeft={XBIData.visibilityLeft}
                                        visibilityRight={XBIData.visibilityRight}
                                        widthComparison={XBIData.widthComparison}
                                        heightComparison={XBIData.heightComparison}
                                        addFunction={() => addXBI(XBIData)}
                                        setVisible={setVisible}
                                        setBasePicture={setBasePicture}
                                        setTargetPicture={setTargetPicture}
                                        key={XBIData.id}
                                    />
                                ))
                            }
                        </AllCards>
                        <button type="button" onClick={sendXBIs}>Adicionar XBIs</button>
                    </>
                ) : loading && <span>carregando...</span>}
            </Content>
            <Modal
                visible={visible}
                setVisible={setVisible}
                basePicture={basePicture}
                targetPicture={targetPicture}
            />
        </>
    );
};

export default Home;
