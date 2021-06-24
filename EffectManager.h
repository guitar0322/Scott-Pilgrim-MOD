#pragma once
#define EFFECT_MIN 3
/*
* ������Ʈ Ǯ�� Ȱ���� ����Ʈ �Ŵ���
* �ּ� EFFECT_MIN���� ����Ʈ���� ����ü�� �����ϰ� �ִٰ�
* ���Ŀ� �߰����� ����Ʈ ���� ��û�� ���� ��� ���ο� ����Ʈ ����ü�� �����ϰ�
* ��û�� ���� ��� ����Ʈ ���� ������ ũ�⸦ EFFECT_MIN���� ����
*/
class EffectManager : public singletonBase<EffectManager>
{
private:
    typedef struct tagEffectInfo {
        int x, y;           //���Ǵ� ��ġ
        int curFrame;       //����Ʈ ����������
        int maxFrame;       //����Ʈ �ִ�������
        float frameTerm;    //����Ʈ �����Ӱ� ����
        float time;         //����Ʈ ������ ���ӽð�
        string clipName;    //Ÿ�� ����Ʈ Ŭ���̸�
        bool active;        //ȭ��ȭ ����
    }EFFECTINFO;
private:
    vector<EFFECTINFO> _effectV;//����Ʈ ������ ���� ����ü ����
    vector<EFFECTINFO>::iterator _effectIter;
public:
    EffectManager();
    ~EffectManager();
    virtual void Init();
    virtual void Release();
    void Update();
    void Render();
    void EmissionEffect(string effectClipName, int x, int y);//x, y�� CLIPMANAGER�� �ִ� Ŭ���� ���
    int GetEffectNum() { return _effectV.size(); }//����Ʈ���� ������ ��ü ũ�⸦ ��ȯ
    int GetActiveNum();//�ּҰ��� 3���� Ȱ��ȭ�� ����Ʈ�� ������ ��ȯ
};


